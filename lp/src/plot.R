
#Plotting performance metric of each measure 

file_name = commandArgs(trailingOnly = TRUE)[1]

iter = as.integer(commandArgs(trailingOnly = TRUE)[2])


setwd("./results/")


data <- read.csv(paste(file_name,".txt",sep=""),head=FALSE,colClasses=c("character","numeric","numeric","numeric"))

file_list <- data[1:(dim(data)[1]/iter),1]



#Calculating Precision

precision <- matrix(unlist(data$V2),nr=length(file_list)) 

avg <- apply(precision,1,mean)

sdev <- apply(precision,1,sd)

png(file=paste(paste("../plots/",paste(file_name,"_PRECISION")),".png"))

if(length(data$V2)==1)
{
  
  sdev=0
  
}

plot(seq(1,length(file_list),1), avg, xaxt = "n",
     ylim=range(c(avg-sdev, avg+sdev)),
     pch=19, xlab="Predictors", ylab="Precision (%)"
)

axis(1, at=seq(1,length(file_list),1), labels=file_list)

arrows(seq(1,length(file_list),1), avg-sdev, seq(1,length(file_list),1), avg+sdev, length=0.1, angle=90, code=3)


#Calculating Auc

auc <- matrix(unlist(data$V3),nr=length(file_list)) 

avg <- apply(auc,1,mean)

sdev <- apply(auc,1,sd)

png(file=paste(paste("../plots/",paste(file_name,"_AUC")),".png"))


if(length(data$V3)==1)
{
  
  sdev=0
  
}

plot(seq(1,length(file_list),1), avg, xaxt = "n",
     ylim=range(c(avg-sdev, avg+sdev)),
     pch=19, xlab="Predictors", ylab="AUC"
)

axis(1, at=seq(1,length(file_list),1), labels=file_list)

arrows(seq(1,length(file_list),1), avg-sdev, seq(1,length(file_list),1), avg+sdev, length=0.1, angle=90, code=3)

#Calculating Running Time

t <- matrix(unlist(data$V4),nr=length(file_list)) 

avg <- apply(t,1,mean)

sdev <- apply(t,1,sd)

png(file=paste(paste("../plots/",paste(file_name,"_time")),".png"))

if(length(data$V4)==1)
{
  
  sdev=0
  
}

plot(factor(file_list), avg, las=2, xlab="Predictors", ylab="Time (secs)")



#plotting ROC curve

png(file=paste(paste("../plots/",paste(file_name,"_ROC")),".png"))

plot(0,0,xlim = c(0,1),ylim = c(-0,1),xlab = "FPR", ylab= "TPR",type = "n")


colors <- rainbow(length(file_list))

for(i in 1:length(file_list))
{
  
  filename <- paste("..",paste(file_list[i],".txt",sep=""),sep="/")
  
  #opening fie_list[i].txt i.e CN.txt or AA.txt etc
  
  data <- read.table(filename,sep=",")
  
  tp_matrix <- matrix(unlist(data$V1),nc=iter)
  
  tp <- apply(tp_matrix,1,mean)
  
  fp_matrix <- matrix(unlist(data$V2),nc=iter)
  
  fp <- apply(fp_matrix,1,mean)
  
  tn_matrix <- matrix(unlist(data$V3),nc=iter)
  
  tn <- apply(tn_matrix,1,mean)
  
  fn_matrix <- matrix(unlist(data$V4),nc=iter)
  
  fn <- apply(fn_matrix,1,mean)
  
  fpr <- fp/(fp+tn)
  
  tpr <- tp/(tp+fn)
  
  lines(fpr,tpr,col=colors[i],type="l",lty=1)
  
}

legend("topright",lty=c(1,1,1,1,1),col=colors,legend = file_list,cex=0.7)


#plotting precision-recall curve



png(file=paste(paste("../plots/",paste(file_name,"_PR")),".png"))

plot(0,0,xlim = c(0,1),ylim = c(-0,1),xlab = "Recall", ylab= "Precision",type = "n")


colors <- rainbow(length(file_list))

for(i in 1:length(file_list))
{
  
  filename <- paste("..",paste(file_list[i],".txt",sep=""),sep="/")
  
  data <- read.table(filename,sep=",")
  
  tp_matrix <- matrix(unlist(data$V1),nc=iter)
  
  tp <- apply(tp_matrix,1,mean)
  
  fp_matrix <- matrix(unlist(data$V2),nc=iter)
  
  fp <- apply(fp_matrix,1,mean)
  
  tn_matrix <- matrix(unlist(data$V3),nc=iter)
  
  tn <- apply(tn_matrix,1,mean)
  
  fn_matrix <- matrix(unlist(data$V4),nc=iter)
  
  fn <- apply(fn_matrix,1,mean)
  
  precision <- tp/(fp+tp)
  
  recall <- tp/(tp+fn)
  
  lines(recall,precision,col=colors[i],type="l",lty=1)
  
}


legend("topright",lty=c(1,1,1,1,1),col=colors,legend = file_list,cex=0.7)




