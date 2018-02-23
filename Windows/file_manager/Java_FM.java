/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package java_fm;

import java.io.File;
import java.io.IOException;
import java.util.Scanner;

/**
 *
 * @author hemo6
 */
public class Java_FM {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws IOException {
        Scanner in = new Scanner(System.in);
        String Name = "";
        String path = "";
        Process pr ;
        File file = new File("D:\\");
        File[] roots=File.listRoots();
        int Point;
        
        while(true)
        {
            System.out.println("-3. Создать файл");
            System.out.println("-2. Создать папку");
            System.out.println("-1. Удалить файл");
            System.out.println("0. Родительский каталог");
            roots = fmSort(roots);
            
            for(int i=0;i < roots.length; i++) 
            {
                path = roots[i].toPath().toString();
                if(roots[i].isFile()) path = "-->"+path+"  @  Скрыт:" + roots[i].isHidden() + "  Размер:" + (float)(roots[i].length()/1024)+ "кБайт";
                System.out.println((i+1)+". "+path);
            }
            Point = in.nextInt();
            switch(Point)
            {
                case -3:
                    System.out.println("Введите имя: ");
                    Name = in.next();
                    File newFile = new File(file.getPath()+File.separator  + Name);
                    newFile.createNewFile();
                    roots = file.listFiles();
                    break;
                case -2:
                    System.out.println("Введите имя: ");
                    Name = in.next();
                    File newFile2 = new File(file.getPath()+File.separator + Name);
                    newFile2.mkdir();
                    newFile2.createNewFile();
                    roots = file.listFiles();
                    break;
                case -1:
                    System.out.println("Введите номер удаляемого файла: ");
                    Point= in.nextInt();
                    if(Point < 1 || Point > roots.length || roots[Point-1].isDirectory())
                    {
                        System.out.println("Ошибка!");
                        break;
                    }
                    roots[Point-1].delete();
                    roots = file.listFiles();
                    break;
                case 0:
                    if(file.getParentFile()!= null) 
                    {
                        file = file.getParentFile();
                        roots = file.listFiles();
                    }
                    else roots = File.listRoots();
                    continue;
                default:
                    if(Point <0 || Point > roots.length )
                    {
                        System.out.println("Ошибка!");
                        break;
                    }
                    if(roots[Point-1].isDirectory())
                    {
                    file = roots[Point-1];
                    roots = file.listFiles();
                    }
                    else pr = Runtime.getRuntime().exec("notepad.exe " + roots[Point-1].getAbsolutePath());
                    break;
            }
            
            
       
        }
    }
    
    public static File[] fmSort(File[] files)
    {
        File Buf;
        int countFiles = files.length;
        for(int e=0;e<countFiles;e++)
        { 
            for(int i=0;i<countFiles;i++)
            {            
                if(files[i].isDirectory())
                {

                   if(i>0 && files[i-1].isFile())
                   {
                       Buf = files[i-1];
                       files[i-1] = files[i];
                       files[i]=Buf;
                   }
                }
            }
        }
        return files;
        
    }
}