public class demo {
    public static void main(String[] args) {
        int[] ids = new int[] { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        String[] names = new String[10];
        // ��ȡ����ĳ���
        System.out.println(names.length);
        System.out.println(ids.length);
        // ��������Ԫ��
        // for (int i = 0; i < ids.length; i++) {
        //     System.out.println(ids[i]);
        // }
        // �����ʼ��ֵ������Ĭ��ֵ��Ϊ��
        // �����Ͷ���0.0
        // char���Ͷ���0����'\u000' Ĭ��Ϊ��
        // ��������Ĭ��ֵ��false
        // �����������;���NULL,(�ַ���) 
        String[] Name[] = new String[]{"����","����","��κ�","���ƿ�"}  
    }
}

class Multiple {
    public static void main(String[] args) {
        for (int i = 1; i <= 9; i++) {
            for (int j = 1; j <= i; j++) {
                System.out.print(j + "*" + i + "=" + i * j + "\t");
            }
            System.out.println();
        }
    }
}