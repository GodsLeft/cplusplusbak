import java.util.HashMap;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.util.Calendar;
public class GetFea{
    public static HashMap<String,Integer> uId_cnt = new HashMap<>(65536);
    public static HashMap<String,Integer> adId_cnt = new HashMap<>(65536);
    public static HashMap<String,Integer> posId_cnt = new HashMap<>(65536);
    public static HashMap<String,Integer> ip_cnt = new HashMap<>(65536);

    public static void hashAdd(HashMap<String,Integer> hash, String key){
        if(hash.containsKey(key)){
            hash.put(key, hash.get(key)+1);
        }else{
            hash.put(key,1);
        }
    }
    public static void scan(String path) throws Exception{
        BufferedReader br = new BufferedReader(new FileReader(path));
        String line = null;
        while((line = br.readLine()) != null){
            String[] fields = line.split(",");
            hashAdd(uId_cnt,fields[0]);
            hashAdd(adId_cnt,fields[2]);
            hashAdd(posId_cnt, fields[3]);
            hashAdd(ip_cnt,fields[6]);
        }
        br.close();
    }

    //产生新的特征
    public static void genData(String src_path, String dst_path, boolean is_train) throws Exception{
        BufferedReader br = new BufferedReader(new FileReader(src_path));
        BufferedWriter bw = new BufferedWriter(new FileWriter(dst_path));

        Calendar cld = Calendar.getInstance();
        cld.set(2015,5,24,0,0,0);
        Long tL = cld.getTimeInMillis()/1000;

        //指向处理的上一行的id
        String OO = "";
        History his = null;
        String line;
        StringBuffer ll = new StringBuffer(130);
        while((line = br.readLine()) != null){
            ll.setLength(0);
            String[] fields = line.split(",");
            ll.append(line+",");
            ll.append(uId_cnt.get(fields[0])); ll.append(",");
            ll.append(adId_cnt.get(fields[2])); ll.append(",");
            ll.append(posId_cnt.get(fields[3])); ll.append(",");
            ll.append(ip_cnt.get(fields[6])); ll.append(",");

            if(!OO.equals(fields[0])){
                his = new History();
                OO = fields[0];
            }
            int hour = (int)(tL - Long.parseLong(fields[7])) / 3600;
            if(his.prev_hour != hour){
                String tmp = (his.history + his.buffer);
                his.history = tmp.substring(tmp.length()-4);
                his.buffer = "";
                his.prev_hour = hour;
            }
            ll.append(his.history);
            his.buffer += fields[8];

            bw.write(ll.toString());
            bw.newLine();
        }
        br.close();
        bw.close();
    }
    //加一个统计时间的函数
    public static void main(String[] args) throws Exception{
        scan(args[0]);
        System.out.println("================Scan complete=========================");
        genData(args[0],args[1],true);
        genData(args[2],args[3],true);
        System.out.println("================Finash GetFea========================");
    }
}

class History{
    public History(){
        history = "0000";
        buffer = "";
        prev_hour = 0;
    }
    public String history;
    public String buffer;
    public int prev_hour;
}

class History1{
    public History1(){}
    public History1(int cap){
        buffer = new StringBuffer(cap);
    }
    public String history;
    public StringBuffer buffer;
    public int prev_hour;
}
