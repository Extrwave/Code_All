# message = "   hellow  "

# print(message.strip()+"hei")
# print(message.lstrip()+"hei")
# print(message.rstrip()+"hei")

# value = '"You need to believe that someting extraordinary is possible."'
# print(value.title())
# print(value.upper())
# print(value.lower())

# print(3+5)
# print(4*2)
# print(12-4)
# print(32/4)

# greet = ['hello', 'great', 'NB']
# print(name[0].title() + greet[2] + ".")

# name = ['GL', 'XYJ', 'ZJH', 'YHB']
# name2 = name.remove('GL')
# print("cannot go to party is " + name[0])
# name.append('HHY')
# name.insert(2, 'ZS')
# print("atten party are " + str(name))
# print("sorry to told that only two person could go to party")

# print(name.pop() + "\ti am sorry")
# print(name.pop() + "\ti am sorry")
# print(name.pop() + "\ti am sorry")
# print("only "+name[0]+" and "+name[1]+" could go to party!")
# del name[0]
# del name[0]
# print(name)

# locate = ['b', 'r', 's', 't', 'a', 'y']
# print(locate)
# print(sorted(locate))
# locate.sort()
# print (locate)
# locate.reverse()
# print(locate)
# locate.reverse()
# print(locate)
# print(len(locate))

# pizzas = ['zisi', 'yidali', 'meisi', 'zhongshi']

# for pizza in pizzas:
#     print(pizza)
#     print("i like " + pizza)
# print("any of those are dilicious!")

# numbers = range(1, 1000001)
# # for number in numbers:
# #     print(number)
# print(sum(numbers))
# print(min(numbers))
# print(max(numbers))

# squar = []
# jishu = range(1, 11)
# for shu in jishu:
#     squar.append(shu**3)
# print(squar)

# squar2 = [value**3 for value in range(1, 11)]  #?????????

# print(str(squar2) + "中文")
# print("中文")
# print("中文")

# print("中文")
# print("中文")
# print("中文")
# print("中文")
# print("中文")
# cars = ['bmw', 'audi', 'toyota', 'subaru']
# print(sorted(cars,reverse=True))
# cars.reverse()
# print(cars)

# litt = [value for value in range(1, 1000001)]
# print(litt[8888:9999])
# print(max(litt))
# print(min(litt))
# print(sum(litt))

# my_food = ['hotpot', 'pizza', 'apple', 'chicken', 'dock']
# friend_food = my_food[:]
# print(my_food[:3])
# print('\n')
# print(friend_food[1:])

# my_food = ['hotpot', 'pizza', 'apple', 'chicken', 'dock']
# your_food = ['牛肉', '猪肉']
# friend_food = my_food[:]
# friend_food.append('牛肉')
# friend_food.remove('pizza')
# del friend_food[-1]
# friend_food.insert(2,'猪肉')

# # for foods in my_food:
# #     print(foods)
# print('\n')
# for ffoods in friend_food:
#     print(ffoods.title())

#切片的学习

# 元组

# yuanzu = ('蚂蚁上树', '红烧茄子', '糖醋排骨')
# for i in yuanzu:
#     print(i)

# yuanzu = ('老麻抄手', '香菇炖鸡')
# print("新的菜单是:")
# for i in yuanzu:
#     print(i)

# str = "www.runoob.com"
# print(str.upper())  # 把所有字符中的小写字母转换成大写字母
# print(str.lower())  # 把所有字符中的大写字母转换成小写字母
# print(str.capitalize())  # 把第一个字母转化为大写字母，其余小写
# print(str.title())
# print(str)  #并不改变其本身的值

######################################################## 判断元素是否在列表或者元组或者字典中
# food = ['hotpot', 'pizza', 'apple', 'chicken', 'dock']
# if 'Hotpot' in food or 'Apple' in food:
#     print("let's go !")
# else:
#     print("NO !")

# alien_color = 'red'
# if alien_color == 'green':
#     print("你获得了5分!")
# elif alien_color == 'red':
#     print("你获得了10分!")

# alient = {}
# alient['colors']='yellow'
# alient['site_x']='20'
# alient['site_y']='50'

# print(alient)

# favorite_languages = {
#     'jen': 'python',
#     'sarah': 'c',
#     'edward': 'ruby',
#     'phil': 'python',
# }

# print("jen's favorite lauguages is " + favorite_languages['jen'])

# for name, language in sorted(favorite_languages.items()):
#     print(name)
#     print(language)

# peoples = {
#     '张三': {
#         'first': '张',
#         'last': '三',
#         '性别': '男',
#         '地址': '重庆市',
#         '喜欢': ['1', '2', '3']
#     },
#     '李四': {
#         'first': '李',
#         'last': '四',
#         '性别': '女',
#         '地址': '上海市',
#         '喜欢': ['1', '2', '3']
#     },
#     '王五': {
#         'first': '王',
#         'last': '五',
#         '性别': '男',
#         '地址': '河南省',
#         '喜欢': ['1', '2', '3']
#     },
#     '赵六': {
#         'first': '赵',
#         'last': '六',
#         '性别': '男',
#         '地址': '重庆市',
#         '喜欢': ['1', '2', '3']
#     },
# }

# for name, name_info in peoples.items():
#     print("\n" + name)
#     for key, value in name_info.items():
#         print(key + "=", end="")
#         print(value)

# promote = "\nPlease enter somme words :"
# promote += "\n9981"

# message = input(promote)
# print(message)

# unconfirmed = ['alice', 'brain', 'cadance']
# confirm = []

# while unconfirmed:
#     current_name = unconfirmed.pop()
#     print("Verifying user:" + current_name.title())
#     confirm.append(current_name)

# for name in confirm:
#     if len(unconfirmed) == 0:
#         print("所有用户均已验证！")
#         break
#     else:
#         print(name)

# sandwich_orders = ['1', '2', '3', '1', '1', '4', '5']
# finshed_sandwich = []

# while sandwich_orders:
#     food = sandwich_orders.pop()
#     print("I made your sandwich :" + food)
#     finshed_sandwich.append(food)
# print(finshed_sandwich)

# while "1" in finshed_sandwich:
#     finshed_sandwich.remove("1")
# print(finshed_sandwich)
# if "1" not in finshed_sandwich:
#     print("\"1\" had sell out!\n")

#-------------统计人名及想要去的地方-------#
# investgate = {}
# mark = True
# while mark:
#     name = input("\n what's your name ?:")
#     place = input("\nwhat place would you like to go ?:")
#     investgate[name] = place
#     cont = input("\nwould like to continue ?  yes or no")
#     if cont == "no":
#         mark = False
# print("Think for your informations!")
# for k, v in investgate.items():
#     print(k + "  would like to go " + v + "\n")

# def Liarbry(book):
#     print("This is my book:" + book)

# books = ['ABC', 'CDE', 'GIF', 'ZXCV']
# for book in books:
#     Liarbry(book)

# def make_album(name, singer):
#     # 它创建一个描述音乐专辑的字典。
#     #   这个函数应接受歌手的名字和专辑名，并
#     #   返回一个包含这两项信息的字典
#     songs = {}
#     songs[name] = singer
#     return songs

# name = input("Please input song's name:")
# singer = input("Please input song's singer:")
# Reback = make_album(name, singer)
# print(Reback)

# def greet_users(names):
#     """向列表中的每位用户都发出简单的问候"""
#     # for name in names:
#     while names:
#         name = names[0]
#         msg = "Hello, " + name.title() + "!"
#         print(msg)
#         names.remove(name)

# usernames = ['hannah', 'ty', 'margot']
# greet_users(usernames[:])
# print(usernames)

# def make_grate(names):
#     for i, name in enumerate(names):
#         mesg = "The Great" + name
#         names[i] = mesg
#         print(name)

# username = ['liuqian', 'guoqian', 'liuyi', 'zhangzhiwei']
# make_grate(username)
# print(username)

# def make_grate(names):
#     for i, name in enumerate(names):
#         mesg = "The Great" + name
#         names[i] = mesg
#         print(name)
#     return names

# username = ['liuqian', 'guoqian', 'liuyi', 'zhangzhiwei']
# newnames = make_grate(username[:])
# print(username)
# print(newnames)

# def add_food(*foods):
#     print("Your sandwitch with: ")
#     for food in foods:
#         mesg = "-" + food
#         print(mesg)

# add_food('mushroom', 'sugar', 'peper')
# def build_profile(first, last, **user_info):
#     """创建一个字典，其中包含我们知道的有关用户的一切"""
#     profile = {}
#     profile['first_name'] = first
#     profile['last_name'] = last
#     for key, value in user_info.items():
#         profile[key] = value
#     return profile

# user_profile = build_profile('桂', '浪', location='china', field='program')
# print(user_profile)

# def car_infomation(brand, version, **car_info):
#     cars = {}
#     cars['brand'] = brand
#     cars['version'] = version
#     for v, k in car_info.items():
#         cars[v] = k
#     return cars

# car = car_infomation('subaru', 'outback', color='blue', tow_package=True)
# print(car)

# import web_sign as QQ
# QQ.saibo("wb", "cs", "sef")
# class Restaurant():
#     """定义方法,其中初始化方法在最前面"""
#     def __init__(self, restaurant_name, cuisine_type):
#         self.restaurant_name = restaurant_name
#         self.cuisine_type = cuisine_type

#     """ 其他的方法紧跟其后，别忘了带上self  """

#     def describle_restaurant(self):
#         print("The restaurant name is :" + self.restaurant_name +
#               "and the type is" + self.cuisine_type)

#     def open_rentaurant(self):
#         print("The reataurant is opening !")

# rest1 = Restaurant('XIAOMING', '川菜')
# rest2 = Restaurant('xiaohong', '粤菜')
# rest3 = Restaurant('xiaogang', '卤菜')

# rest1.describle_restaurant()
# rest1.open_rentaurant()
# rest2.describle_restaurant()
# rest3.describle_restaurant()

# class User():
#     def __init__(self, first_name, last_name):
#         self.first_name = first_name
#         self.last_name = last_name

#     def describle_user(self):
#         print("The name is " + self.first_name + " " + self.last_name)

#     def greet_user(self):
#         print("Nice to meet you " + self.first_name + " " + self.last_name +
#               " !")

# user1 = User('Xiao', 'Ming')
# user2 = User('Xiao', 'Hong')
# user3 = User('Xiao', 'Gang')
# user1.describle_user()
# user1.greet_user()

# class Restaurant():
#     """定义方法,其中初始化方法在最前面"""
#     def __init__(self, restaurant_name, cuisine_type):
#         self.restaurant_name = restaurant_name
#         self.cuisine_type = cuisine_type

#     """ 其他的方法紧跟其后，别忘了带上self  """

#     def describle_restaurant(self):
#         print("The restaurant name is :" + self.restaurant_name +
#               "and the type is" + self.cuisine_type)

#     def open_rentaurant(self):
#         print("The reataurant is opening !")

# class IcecreamStand(Restaurant):
#     """初始化父类属性"""
#     def __init__(self, restaurant_name, cuisine_type, *flavors):

#         super().__init__(restaurant_name, cuisine_type)
#         """初始化子类属性"""
#         self.flavors = flavors
#         self.number = 100

#     def List_flavors(self):
#         print("Our stand have flavors: ")
#         for flavor in self.flavors:
#             print(flavor)

# my_store = IcecreamStand('十六的小摊摊', '自营', 'apple', 'strawberry', 'pears',
#                          'banana')
# my_store.describle_restaurant()
# my_store.open_rentaurant()
# my_store.List_flavors()
# print(my_store.number)

# class Car():
#     def __init__(self, brand, year, aera):
#         self.brand = brand
#         self.year = year
#         self.aera = aera
#         self.miles = 0

#     def Message(self):
#         print(self.brand + self.year + self.aera)
#         print("The car have run " + str(self.miles) + " m")
#         print("left gas are: " + str(self.gas) + " L")

#     def chang_miles(self, number):
#         if (number < self.miles):
#             print("Please don't chang miles back !")
#         else:
#             self.miles = number

#     def icrease_miles(self, number):
#         self.miles += number

#     def icrease_gas(self, number):
#         self.gas = number

# class Battery():
#     def __init__(self, battery_size=80):
#         self.battery_size = battery_size

#     def describle_battery(self):
#         print("This car has a " + str(self.battery_size) + "-kWh battery.")

# class Battery_Cars(Car):
#     def __init__(self, brand, year, area):
#         super().__init__(brand, year, area)
#         self.Battery = Battery()
#         self.miles = 0
#         self.gas = 0

#     def icrease_gas(self, number):
#         print("The electric_Car have not gas! ")

#     def Message(self):
#         print(self.brand + self.year + self.aera)
#         print("The car have run " + str(self.miles) + " km")

# little_car = Battery_Cars('雪佛兰', '2025', '四川成都')
# little_car.chang_miles(10)
# little_car.icrease_miles(5)
# little_car.icrease_gas(30)
# little_car.Battery.describle_battery()
# little_car.Message()

# with open('F:\AEx_Code\Py_files\Python_files\pai.txt') as file_object:
#     contents = file_object.read()
#     print(contents.rstrip())

# with open('F:\AEx_Code\Py_files\Python_files\pai.txt') as file_object:
#     contents = file_object.read()
# print(contents)

# with open('F:\AEx_Code\Py_files\Python_files\pai.txt') as file_object:
#     contents = file_object.readlines()
#     for message in contents:
#         print("The message is :" + message.replace('python', 'java').strip())
#         index = 'python'

# if index in message:
#     print("yes!")
# else:
#     print("No!")

##   r+ 追加内容是从文件头开始在追加的，如果要从文件末尾追加需要   a+
with open('F:\AEx_Code\Py_files\Python_files\pai.txt', 'r') as file_object:
    content = file_object
    # content.writelines("happy everyday !!!\n")
    for line in file_object:
        print(line)
# print(contents)