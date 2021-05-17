// import java.util.Arrays;

// import java.util.Arrays;

// class App {

// public static void main(String[] args) {
// int temp;
// int[] arr = new int[] { 23, 31, 42, 53, 12, 34, 76, 34, 88, 99, 10 };
// int[] arr2 = new int[] { 23, 31, 42, 53, 12, 34, 76, 34, 88, 99, 10 };
// // 排序
// for (int i = 0; i < arr.length; i++) {
// System.out.print(arr[i] + "\t");
// }
// for (int i = 0; i < arr.length; i++) {
// for (int j = 0; j < arr.length - i - 1; j++) {
// if (arr[j] > arr[j + 1]) {
// temp = arr[j];
// arr[j] = arr[j + 1];
// arr[j + 1] = temp;
// }
// }
// }
// // System.out.println();
// // for (int i = 0; i < arr.length; i++) {
// // System.out.print(arr[i] + "\t");
// // }
// System.out.println(Arrays.toString(arr));
// Arrays.sort(arr2);
// System.out.println(Arrays.toString(arr2));
// int index = Arrays.binarySearch(arr2, 53);
// System.out.println(index);// 返回的是序号
// }
// }
public class App {
    public static void main(String[] args) {
        Person xiaomi = new Person();
        xiaomi.study("xiaomi");
        xiaomi.showAge();
        xiaomi.addAge();
    }
}

// pop面向过程 oop面向对象
class Person {
    String name;
    int sex;
    int age;

    void study(String na) {
        name = na;
        System.out.println(name);
    }

    void showAge() {
        System.out.println(age);
    }

    void addAge() {
        age += 2;
        System.out.println(age);
    }
}

