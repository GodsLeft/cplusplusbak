import java.io.*;
import java.util.Calendar;
public class GetVa{
    public static void getVa(String src, String dst) throws Exception{
        BufferedReader br = new BufferedReader(new FileReader(src));
        BufferedWriter bw = new BufferedWriter(new FileWriter(dst));
        Calendar cld = Calendar.getInstance();
        cld.set(2015,4,22,0,0,0);
        Long tL = cld.getTimeInMillis()/1000;
        System.out.println(tL);

        String line;
        while((line = br.readLine()) != null){
            String[] fields = line.split(",");
            if(Long.parseLong(fields[7]) > tL){
                bw.write(line);
                bw.newLine();
            }
        }
        br.close();
        bw.close();
    }
    public static void main(String[] args) throws Exception{
        getVa(args[0],args[1]);
        System.out.println("====================Finash=================");
    }
}
