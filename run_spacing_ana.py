import subprocess


#root -e "#include \"SiSpect.h\"" -e "#include \"SiSpect.C\""
for pmidx, pm in enumerate(["minus", "plus"]):
    for run in range(10):
        # start to create run files
        # Inner set of pixel detectors
        sawInnerSet = False
        sawOuterSet = False
        sawAll = False
        new_file = ""
        with open("runfiles/start.mac") as file:
            for line in file.readlines():
                if sawAll:
                    new_file += line
                    continue
                if not sawOuterSet and "Inner set of pixel detectors" in line:
                    new_file += line
                    sawInnerSet = True
                    continue
                if sawInnerSet and "Outer set of pixel detectors" in line:
                    new_file += line
                    sawInnerSet = False
                    sawOuterSet = True
                    continue
                if "Kapton" in line:
                    new_file += line
                    sawAll = True
                    continue
                if sawInnerSet and "/musr/command" in line:
                    new_file += line
                    continue
                if sawOuterSet and "/musr/command" in line:
                    curLine = ""
                    s = line.replace("   "," ").replace("  ", " ").split(" ")
                    cur_s = line.replace("   "," ").replace("  ", " ").split(" ")
                    for i, si in enumerate(s):
                        if si == "log_World" and cur_s[i-1] == "20.0":
                            if pm == "minus":
                                cur_s[i-1] = str(float(cur_s[i-1])-run)
                            if pm == "plus":
                                cur_s[i-1] = str(float(cur_s[i-1])+run)
                        if si == "log_World" and cur_s[i-1] == "-20.0":
                            if pm == "minus":
                                cur_s[i-1] = str(float(cur_s[i-1])+run)
                            if pm == "plus":
                                cur_s[i-1] = str(float(cur_s[i-1])-run)
                    for s in cur_s:
                        curLine += s
                        curLine += " "
                    new_file += curLine
                    continue
                new_file += line

        with open(f"runfiles/400{run}_{pm}.mac", "w") as file:
            file.write(new_file)

        subprocess.run(f"musrsim/build/musrSim runfiles/400{run}_{pm}.mac", shell=True)
        subprocess.run(f"mv data/musr_0.root data/musr_400{run}_{pm}.root", shell=True)

        root_script = ""
        root_script += "#include \"SiSpect.h\"\n"
        root_script += "#include \"SiSpect.C\"\n"

        root_script += f"void run_spacing_ana_{run}_{pm}"
        root_script += "() {\n"
        root_script += f"TFile* fin=new TFile(\"data/musr_400{run}_{pm}.root\");\n"
        root_script += "SiSpect t;\n"
        root_script += f"t.QCoinIO(true, 0, {pmidx*10+run});\n"
        root_script += "}"

        with open(f"run_spacing_ana_{run}_{pm}.C", "w") as file:
            file.write(root_script)

        subprocess.run(f"root -q run_spacing_ana_{run}_{pm}.C", shell=True)
        subprocess.run(f"rm run_spacing_ana_{run}_{pm}.C", shell=True)


