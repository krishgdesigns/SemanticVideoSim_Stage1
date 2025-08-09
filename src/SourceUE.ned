package selfmade;
simple SourceUE {
    parameters:
        string gdfFile;
        volatile double sendInterval @unit(s);  // Add unit
    gates:
        input in;
        output out;
}
