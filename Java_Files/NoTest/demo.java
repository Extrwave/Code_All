public class demo {
    public static void main(String[] args) {
        int[] ids = new int[] { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        String[] names = new String[10];
        // 获取数组的长度
        System.out.println(names.length);
        System.out.println(ids.length);
        // 遍历数组元素
        // for (int i = 0; i < ids.length; i++) {
        //     System.out.println(ids[i]);
        // }
        // 数组初始化值，整型默认值都为零
        // 浮点型都是0.0
        // char类型都是0或者'\u000' 默认为空
        // 布尔类型默认值是false
        // 引用数据类型就是NULL,(字符串) 
        String[] Name[] = new String[]{"杨虹彬","桂浪","朱嘉浩","熊云俊"}  
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