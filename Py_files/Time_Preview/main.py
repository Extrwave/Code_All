import pandas as pd
import numpy as np
from scipy import stats
import matplotlib.pyplot as plt
import statsmodels.api as sm
from statsmodels.graphics.api import qqplot


#读取数据，进行处理
dta = [79,95,98,51,275,67,63,40,50,31,38,43,58,28,44,14,148,87,23,42,49,33,65,68,54,129,68,71,107,119,59,50,46,44,40,63,67,76,73,44,138,146,72,30,41,26,25,36]
dta = np.array(dta,dtype=np.float)
dta = pd.Series(dta)

#对数据进行绘图，观测是否是平稳时间序列
dta.index = pd.Index(sm.tsa.datetools.dates_from_range('2000','2047'))
dta.plot(figsize=(12,8))
plt.show()

fig = plt.figure(figsize=(12,8))
ax1 = fig.add_subplot(111)
diff1 = dta.diff(1)
diff1.plot(ax=ax1)
plt.show()

#选择合适的p,q
diff1 = dta.diff(1)
fig = plt.figure(figsize=(12,8))
ax1 = fig.add_subplot(211)
fig = sm.graphics.tsa.plot_acf(dta,lags=40,ax=ax1)
ax2 = fig.add_subplot(212)
fig = sm.graphics.tsa.plot_acf(dta,lags=40,ax=ax2)
# plt.show()

#获取最佳模型
arma_mod70 = sm.tsa.ARMA(dta,(7,0)).fit()
print(arma_mod70.aic,arma_mod70.bic,arma_mod70.hqic)
arma_mod30 = sm.tsa.ARMA(dta,(0,1)).fit()
print(arma_mod30.aic,arma_mod30.bic,arma_mod30.hqic)
arma_mod71 = sm.tsa.ARMA(dta,(7,1)).fit()
print(arma_mod71.aic,arma_mod71.bic,arma_mod71.hqic)
arma_mod80 = sm.tsa.ARMA(dta,(8,0)).fit()
print(arma_mod80.aic,arma_mod80.bic,arma_mod80.hqic)

#模型检验
resid = arma_mod80.resid
fig = plt.figure(figsize=(12,8))
ax1 = fig.add_subplot(211)
fig = sm.graphics.tsa.plot_acf(dta,lags=40,ax=ax1)
ax2 = fig.add_subplot(212)
fig = sm.graphics.tsa.plot_acf(dta,lags=40,ax=ax2)
plt.show()

print(sm.stats.durbin_watson(arma_mod80.resid.values))

fig = plt.figure(figsize=(12,8))
ax = fig.add_subplot(111)
fig = qqplot(resid,line='q',ax=ax,fit=True)
plt.show()

r,q,p = sm.tsa.acf(resid.values.squeeze(),qstat=True)
data = np.c_[range(1,41),r[1:],q,p]
table = pd.DataFrame(data,columns=['lag','AC','Q','Prob(>Q)'])
print(table.set_index('lag'))

#模型预测
predict_sunspots = arma_mod80.predict('2047','2059',dynamic=True)
print(predict_sunspots)
fig,ax = plt.subplots(figsize=(12,8))
ax = dta.ix['2000':].plot(ax=ax)
fig = arma_mod80.plot_predict('2047','2059',dynamic=True,ax=ax,plot_insample=False)
plt.show()

