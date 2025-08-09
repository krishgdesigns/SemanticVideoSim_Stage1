package selfmade;
simple ReceiverUE {
    parameters:
        string logFile;
        int id;
    gates:
        input in;
        output out; // to gNodeB (ACK)
}
