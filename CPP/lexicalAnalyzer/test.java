package com.test;
import java.util.*;

public strictfp class Demo {
    synchronized void demoMethod() throws IOException {
        native void nativeCall();
        strictfp double calc() { return 0.0; }
        transient List<String> list = new ArrayList<>();
    }
}
