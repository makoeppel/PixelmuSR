# Run Simulation
```bash
musrsim/build/musrSim runfiles/xxxx.mac
```

# Run SiSpect.C
```bash
TFile* fin=new TFile("data/musr_1021.root");
.L SiSpect.C
SiSpect t
t.QCreateIO(true, 0.7, 1) # FigFlag=true, eCut=0.7 [MeV], run=1
t.QCoinIO(true, 0.7)
```
