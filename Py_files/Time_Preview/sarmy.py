# 导入第三方模块
import scipy.stats as stats
import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns
from sklearn import model_selection
import statsmodels.api as sm

# 中文和负号的正常显示
plt.rcParams['font.sans-serif'] = ['Microsoft YaHei']
plt.rcParams['axes.unicode_minus'] = False

# 读取数据
gdp_data = pd.read_csv('train.csv',encoding='gbk',index_col=0)
# data.columns = ['类别', '月份1-12']
# 将数据集拆分为训练集和测试集
train,test = model_selection.train_test_split(gdp_data ,test_size=0.2,random_state=6)
# 根据训练集train进行建模
model = sm.formula.ols('类别 ~ 一月 + 二月 + 三月 + 四月 + 五月 + 六月 + 七月 + 八月 + 九月 + 十月 + 十一月 + 十二月',data=train).fit()
print('模型的偏回归系数分别为：\n',model.params)

# 剔除测试集test中的 次数 变量，用剩下的自变量进行预测
test_x = test.drop(labels='类别',axis=1)
pred = model.predict(exog = test_x)
print('\n对比预测值和实际值的差异：\n',pd.DataFrame({'predict_y':pred,'real_y':test['类别']}))
