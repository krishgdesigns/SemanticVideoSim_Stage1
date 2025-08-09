package selfmade;
simple gNodeB {    
    parameters:
        int numReceivers;
        volatile double broadcastDelay @unit(s);  //  Add unit
        volatile double ackTimeout @unit(s);      //  Add unit
    gates:
        input in;
        output out[numReceivers];
        input ackIn[numReceivers];
        output ackOut;
}
