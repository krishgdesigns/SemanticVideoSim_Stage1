# 📡 SemanticVideoSim_Stage1

**Custom-built OMNeT++ wireless simulation for semantic-aware video frame transmission (Stage 1).**

---

## 📖 Overview 
This project implements a **semantic-aware video transmission system** using OMNeT++.  
A pre-processed video frame selection file (CSV/GDF) determines which frames are sent from a Source UE to a gNodeB, which then broadcasts to multiple receiving UEs.  

It is a **custom-built OMNeT++ wireless simulation** created **without INET or Simu5G dependencies**, demonstrating the complete transmission flow of selected video frames between network nodes.

The system is designed as the foundation for progressive integration with INET and Simu5G in later stages.

**Key features:**
- 📡 5G-like wireless transmission (abstracted logic)
- 🎯 Frame selection based on semantic relevance
- 📊 Logging: per-UE throughput, delay, delivery flags
- 🔄 ACK & retransmission from gNodeB
- 🏃 UE mobility patterns (stationary/circular/opposite direction)

---

## 📂 Project Structure
selfmade/
├── .gitignore
├── README.md
├── Makefile
├── gdf/                 # Input GDF files with selected frame list
├── simulations/
│   ├── omnetpp.ini      # Simulation configuration
│   ├── package.ned      # Simulation package definition
│   ├── run              # Run script
│   └── gdf -> ../gdf    # Symlink to GDF folder
├── src/
│   ├── FrameMsg.msg     # OMNeT++ message definition for frame transmission
│   ├── FrameSender.cc/h # Source UE frame sending logic
│   ├── FrameReceiver.cc/h # Receiver UE frame handling logic
│   ├── SourceUE.ned     # NED definition for Source UE
│   ├── gNodeB.ned       # NED definition for gNodeB
│   ├── ReceiverUE.ned   # NED definition for Receiver UEs
│   ├── SimpleWirelessChannel.ned # Custom wireless channel
│   ├── package.ned
│   └── selfmade         # Compiled binary
└── out/                 # Simulation output (ignored in Git)


---

## 🎯 Stage 1 Goals (Achieved)
- Build a self-contained wireless simulation entirely in OMNeT++ core modules.  
- Implement a GDF/CSV-driven frame selection mechanism.  
- Model one Source UE sending selected frames to a gNodeB, which then broadcasts them to Receiver UEs.  
- Add acknowledgment and retransmission logic between nodes.  
- Log per-UE reception data in `.gdf` format for analysis.  

---

## 🛠 Features Implemented in Stage 1

### 1️⃣ Custom Wireless Channel
- Created using OMNeT++ `.ned` definitions, no external frameworks.
- Configurable transmission delay and loss probability.

### 2️⃣ Application Logic
- **SourceUE** reads a GDF file containing selected frames to send.
- **gNodeB** forwards incoming frames to all connected ReceiverUEs.
- **ReceiverUEs** log received frames and send ACKs back.

### 3️⃣ Reliability
- ACK timeout and retransmission mechanism in SourceUE and gNodeB.

### 4️⃣ Logging & Analysis
- Per-UE logs written in `.gdf` format for easy post-simulation processing.

---

## 🚀 How to Run the Simulation

### **1. Compile the project**
```bash cd ~/omnetpp-6.0.1/samples/selfmade
            make
```bash - cd simulations
           ./run

### Outputs:Simulation results in .vec and .sca format.Generated output.gdf files for each UE in the gdf/ directory.

###📊 Stage 1 Results & Observations
Traffic Pattern: Frames are sent at a fixed interval (CBR-like), determined in FrameSender.cc.
Reliability: ACK timeout ensures retransmissions for lost frames.
Scalability: Tested with 1 Source UE, 1 gNodeB, and 10 Receiver UEs.

###🗺 Project Roadmap
✅Stage 1 – Custom OMNeT++ Wireless Simulation (Completed)
Fully custom channel and node models.Frame selection from GDF and broadcasting logic.ACK and retransmission handling.

🔄Stage 2 – INET Framework Integration (Next)
Import Stage 1 topology into INET.

Use INET’s:WirelessMedium for realistic channel modeling.Mobility models (RandomWaypoint, LinearMobility, etc.).Built-in network & MAC protocols.
Preserve Stage 1’s application layer logic, integrate into INET hosts.

🚀Stage 3 – 5G & Simu5G Integration (Planned )
Replace INET hosts with Simu5G NRUe and gNodeB.Implement realistic 5G NR PHY/MAC layers.Support broadcast/multicast over 5G NR.Add advanced KPIs: latency, jitter, throughput, RLC retransmissions.

📜 License
This project is released under the MIT License – you are free to use, modify, and distribute it with attribution.

