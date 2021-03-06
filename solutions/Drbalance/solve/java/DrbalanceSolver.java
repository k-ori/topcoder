import java.io.FileReader;
import java.io.FileWriter;

import java.util.List;
import java.util.ArrayList;

import org.topcoder.TopcoderReader;
import org.topcoder.TopcoderWriter;
import org.topcoder.TypeRef;

public class DrbalanceSolver {
    public static void main(String[] args) {
    try {
        TopcoderReader reader = new TopcoderReader(new FileReader(args[0]));
        String s = (String) reader.next(String.class);
        reader.next();
        
        int k = (Integer) reader.next(Integer.class);
        reader.close();

        Drbalance solver = new Drbalance();
        TopcoderWriter writer = new TopcoderWriter(new FileWriter(args[1]));
        writer.write(solver.lesscng(s, k));
        writer.close();
    } catch (Exception err) {
        err.printStackTrace(System.err);
    }
    }    
}
