# WorkSpace
多个工作项目的git仓库
只需要将每个项目的总文件夹，复制到仓库，并设置需要忽略的文件
然后同步即可，如果无法同步，尝试删除配置

## 下面是一些常用 git Cmd：<br>
### 设置用户名
git config --global user.name chai21sks <br>
### 设置邮件地址
git config --global user.email xxxx@xx.com <br>
### 删除网络配置
git config --global --unset http.proxy <br>
#### 清理DNS
ipconfig /flushdns <br>
### 创建初始化本地仓库
git init <br>
### 克隆 github 仓库
git clone https://github.com/chaimark/WorkSpace.git <br>
### 修改本地仓库当前分支名字
git branch -m master main <br>
### 连接到 github 仓库
git remote add WorkSpace https://github.com/chaimark/WorkSpace.git <br>
### 拉取 github 仓库的文件
git pull WorkSpace main:main <br>
### 添加文件到暂存区
git add * <br>
### 提交到本地仓库
git commit -m "massage" <br>
### 推送文件到 github 仓库
git push -u WorkSpace main:main <br>
### 新建分支
git branch master <br>
### 切换分支
git checkout master <br>
### 删除分区
git branch -d master <br>

