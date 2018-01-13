package com.tools;

import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

/**
 * �ļ�������
 * 
 * @author hasee
 */
public class FileOperationTools {

//	public static void main(String[] args) throws IOException {
//		String read = readFromFile("./input.txt");
//		System.out.println(read);
//	}

	/**
	 * ���ļ�����-���ַ�����
	 * @param filepath : �ļ�·��
	 * @throws IOException
	 */
	public static String readFromFile(String filepath) throws IOException {
		StringBuffer buffer = new StringBuffer();
		FileReader fileReader = null;
		try {
			File file = new File(filepath);
			// ����ļ������ڣ�����һ���µĿ��ļ�
			if (!file.exists()) {
				file.createNewFile();
			}
			fileReader = new FileReader(file);
			// ÿ�ζ���1024�ֽ�
			char[] buf = new char[1024];
			int charread = 0;
			while ((charread = fileReader.read(buf)) != -1) {
				String str = new String(buf);
				buffer.append(str);
			}
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			// ��д���ļ�ִ�йرղ������ͷ���Դ
			try {
				if (fileReader != null) {
					fileReader.close();
				}
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
		return buffer.toString();
	}

	/**
	 * д�����
	 * @param str : ���ε��ս������ս��
	 * @param type �� ��������
	 */
	public static void writeToFile(String str, String type) {
		String pathname = "./output.txt";
		File file = null;
		FileWriter fileWriter = null;
		try {
			file = new File(pathname);
			// �������ڣ�ֱ���´���һ���ļ�
			if (!file.exists()) {
				file.createNewFile();
				System.out.println("�ļ������ڣ����´���һ��");
			}
			fileWriter = new FileWriter(file.getName(), true);
			String message = "<" + str + "," + type + ">";
			fileWriter.write(message + "\n");
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			// ������ϣ��ͷ�����
			try {
				if (fileWriter != null) {
					fileWriter.close();
				}
			} catch (Exception e2) {
				e2.printStackTrace();
			}
		}
		System.out.println("*");
	}

}
