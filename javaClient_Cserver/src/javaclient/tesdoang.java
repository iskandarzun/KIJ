/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package javaclient;
 import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileReader;
import java.io.InputStream;
import java.io.InputStreamReader;
/**
 *
 * @author Fathur
 */
public class tesdoang {

   public static void main(String[] args) throws Exception {
      
      String thisLine = "";
      String Gabungan = "";
      int tes= 0; int ctr = 0;
      try{
         // open input stream test.txt for reading purpose.
         BufferedReader br = new BufferedReader(new FileReader("D:/test.txt"));
         while ((thisLine =  br.readLine()) != null) {
             ctr++;
              System.out.println(thisLine + ctr);
             }
        // System.out.println(tes + ctr);
      }catch(Exception e){
         e.printStackTrace();
      }
   }
}

