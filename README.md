## 去除 .sh 中 \r
sed -i 's/\r//' initLinux

## WorkSpace
多个工作项目的git仓库
只需要将每个项目的总文件夹，复制到仓库，并设置需要忽略的文件
然后同步即可，如果无法同步，尝试删除配置

## 下面是一些常用 git Cmd
### 设置用户名
git config --global user.name chai21sks
### 设置邮件地址
git config --global user.email xxxx@xx.com
#### 清理DNS
ipconfig /flushdns
### 设置git代理网络配置
git config --global http.proxy '127.0.0.1:7890'
git config --global https.proxy '127.0.0.1:7890'
### 取消git代理网络配置
git config --global --unset http.proxy
git config --global --unset https.proxy
### 创建初始化本地仓库
git init
### 克隆 github 仓库
git clone https://github.com/chaimark/WorkSpace.git
### 修改本地仓库当前分支名字
git branch -m master main
### 连接到 github 仓库
git remote add origin https://github.com/chaimark/WorkSpace.git
### 设置远程仓库的名字
git remote rename origin WorkSpace
### 拉取 github 仓库的文件
git pull origin main:main
### 查看当前分支的所有文件
git status
### 添加文件到暂存区
git add *
### 提交到本地仓库
git commit -m "massage"
### 推送文件到 github 仓库
git push origin main:main
### 新建分支
git branch master
### 切换分支
git checkout master
### 删除分区
git branch -d master
### 查看当前分支
git branch


