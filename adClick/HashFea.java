import java.io.*;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
class HashFile extends Thread{
    public String spath;
    public String dpath;
    public int isTrain;
    public HashFile(){}
    public HashFile(String src,String dst,int isTrain){
        this.spath = src;
        this.dpath = dst;
        this.isTrain = isTrain;
    }
    //拆分一个大文件
    public static int split(String path, int n) throws Exception{
        BufferedReader br = new BufferedReader(new FileReader(path));
        int idx = 0;
        String line;
        int lineNum = 0;
        BufferedWriter bw = null;
        while((line = br.readLine()) != null){
            if(lineNum%100_0000 == 0){    //没 分一个文件
                idx += 1;
                if(idx != 1){
                    bw.close();
                }
                if(n == 1){
                    bw = new BufferedWriter(new FileWriter(".tr_"+idx));
                }else{
                    bw = new BufferedWriter(new FileWriter(".va_"+idx));
                }
            }
            lineNum++;
            bw.write(line);
            bw.newLine();
        }
        bw.close();
        return idx;
    }

    public static String byteArray2Hex(byte[] byteArray){
        char[] hexDigits = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
        char[] resultCharArray = new char[byteArray.length * 2];
        int index = 0;
        for(byte b:byteArray){
            resultCharArray[index++] = hexDigits[b >>> 4 & 0xf];
            resultCharArray[index++] = hexDigits[b & 0xf];
        }
        return new String(resultCharArray);
    }
    public static String hashString(String input, String algorithm) throws NoSuchAlgorithmException{
        MessageDigest digest = MessageDigest.getInstance(algorithm);
        byte[] inputByteArray = input.getBytes();
        digest.update(inputByteArray);
        byte[] resultByteArray = digest.digest();

        return Integer.parseInt(byteArray2Hex(resultByteArray).substring(26),16) % 1000000 + "";
    }

    public static String hashString(String input) throws NoSuchAlgorithmException{
        return hashString(input,"MD5");
    }

    //哈希特征
    public static void hashfea(String spath,String dpath, int isTrain) throws Exception{
        String line;
        BufferedReader br = new BufferedReader(new FileReader(spath));
        BufferedWriter bw = new BufferedWriter(new FileWriter(dpath));
        StringBuffer feats = new StringBuffer(400);

        while((line = br.readLine()) != null){
            String[] fields = line.split(",");
            feats.setLength(0);
            feats.append(fields[0]+"_"+fields[3]+" ");
            if(isTrain == 1){
                feats.append(fields[8]+" ");
            }else{
                feats.append("0 ");
            }
            feats.append(hashString(fields[0]) + " ");
            feats.append(hashString(fields[2]) + " ");
            feats.append(hashString(fields[3]));feats.append(" ");
            feats.append(hashString(fields[4]));feats.append(" ");
            feats.append(hashString(fields[5]));feats.append(" ");
            feats.append(hashString(fields[6]));feats.append(" ");
            feats.append(hashString(fields[13]));feats.append(" ");

            if(Integer.parseInt(fields[12]) > 1000){
                feats.append(hashString(fields[6]) + " ");
            }else{
                feats.append(hashString(fields[12])+ " ");
            }
            if(Integer.parseInt(fields[9]) > 1000){
                feats.append(hashString(fields[0]) + " ");
            }else{
                feats.append(hashString(fields[9]) + " ");
            }
            if(Integer.parseInt(fields[10]) > 1000){
                feats.append(hashString(fields[2]) + " ");
            }else{
                feats.append(hashString(fields[10]) + " ");
            }
            if(Integer.parseInt(fields[11]) > 1000){
                feats.append(hashString(fields[3]) + " ");
            }else{
                feats.append(hashString(fields[11]) + " ");
            }

            if(Integer.parseInt(fields[9]) > 30){
                feats.append(hashString(fields[9]));
            }else{
                feats.append(hashString(fields[9] + fields[13]));
            }

            bw.write(feats.toString());
            bw.newLine();

        }
        bw.close();

    }
    @Override
    public void run(){
        try{
            hashfea(spath,dpath,isTrain);
        }catch(Exception e){
            e.printStackTrace();
        }
    }
}
//这里实际上还是单线程的
public class HashFea{
    public static void main(String[] args) throws Exception{
        int fileNum = HashFile.split(args[0],1);
        for(int i = 1;i<= fileNum;i++){
            HashFile hf = new HashFile(".tr_"+i, ".tr_f_"+i,1);
            hf.start();
        }
        System.out.println("============tr hash finash========");

        int vafileNum = HashFile.split(args[1],0);
        for(int i=1;i<= vafileNum;i++){
            HashFile hf = new HashFile(".va_"+i, ".va_f_"+i,0);
            hf.start();
        }
        System.out.println("============va hash finash========");
    }
}

