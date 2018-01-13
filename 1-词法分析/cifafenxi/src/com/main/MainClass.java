package com.main;

import java.io.File;
import java.io.FileReader;
import java.io.IOException;

import com.tools.Analysis;
import com.tools.FileOperationTools;

public class MainClass {
	
	/**
	 * ������
	 * @param args
	 * @throws IOException
	 */
	public static void main(String[] args) throws IOException {
		FileReader fileReader = null;
		try {
			File file = new File("./output.txt");
			// ����ļ������ڣ�����һ���µĿ��ļ�
			if (file.exists()) {
				file.delete();
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
		//��ȡ�ļ�·��
		String readfilepath = "./input.txt";
		//���� readFromFile() �������ļ���ȡ�� String ���ͷ���
		String readStr = FileOperationTools.readFromFile(readfilepath);
		//ֱ�ӽ� string ����analysis() �������з���
		Analysis.analysis(readStr);
	}

}
