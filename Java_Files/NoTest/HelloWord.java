// public class HelloWord { 

//     public static void main(String[] args) { 
//         System.out.println("HelloWord!");
//     }
// }

// class HelloWord {
//     public static void main(String[] args) {
//         int myAge = 19;
//         int myWeight = 126;
//         System.out.println("HelloWorld");
//         System.out.println(myAge + myWeight);
//     }
// }

// /**
//  * byte short char 之间的运算都会转化为 int 型
//  * 
//  * 
//  * 
//  * + 表示链接的话，前后必须有一个是字符串
//  */

// class Cancu {
//     static void main(String[] args) {

//         byte a1 = 12;
//         int a2 = 234;
//         int a3 = a1 + a2;
//         String b1 = "";
//         System.out.println(a3);
//         System.out.println("\n");
//         System.out.println(b1);
//     }
// }
// import java.util.Scanner;

// class HelloWord {
//     public static void main(String[] args) {
//         Scanner scan = new Scanner(System.in);
//         String num = scan.nextLine();
//         System.out.println(num);
//         scan.close();
//     }
// }

class HelloWorld {

    public static void main(String[] args) {
        int temp;
        int[] arr = new int[] { 23, 31, 42, 53, 12, 34, 76, 34, 88, 99, 10 };
        // 冒泡排序
        for (int i = 0; i < arr.length; i++) {
            System.out.println(arr[i] + "\t");
        }
        for (int i = 0; i < arr.length; i++) {
            for (int j = 0; j < arr.length - i; j++) {
                if (arr[i] > arr[j]) {
                    temp = arr[j];
                    arr[j] = arr[i];
                    arr[i] = temp;
                }
            }
        }
        for (int i = 0; i < arr.length; i++) {
            System.out.println(arr[i] + "\t");
        }
    }
}