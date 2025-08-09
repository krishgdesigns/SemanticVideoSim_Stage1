cat > README.md <<'EOF'
# SemanticVideoSim_Stage1

**Custom-built OMNeT++ wireless simulation for semantic-aware video frame transmission (Stage 1).**

## 📌 Overview
This project implements a **semantic-aware video transmission system** using OMNeT++.  
A pre-processed video frame selection file (CSV/GDF) determines which frames are sent from a source UE to a gNodeB, which then broadcasts to multiple receiving UEs.

Key features:
- 📡 5G-like wireless transmission (abstracted logic)
- 🎯 Frame selection based on semantic relevance
- 📊 Logging: per-UE throughput, delay, delivery flags
- 🔄 ACK & retransmission from gNodeB
- 🏃 UE mobility patterns (stationary/circular/opposite direction)

## 🗂 Project Structure
