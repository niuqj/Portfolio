# AI_RAW_NR

独立完成 AI RAW 降噪模型的研究与实现。模型规模为 **1.08M 参数**，处理一张 **1080p 图像约需 9.322 GMACs**。以下展示模型在低照度实拍图像上的降噪效果；图像处理流程包含黑电平校正、自动白平衡、自动曝光、去马赛克和模型降噪。

> 拍摄照度约为 **1–0.1 lux**。以下均为左右对比图：左侧为处理前，右侧为模型降噪后；为便于观察细节，保留原始全分辨率。

## 效果对比

### 自动采集图像

#### cam0_still_000007_in

![cam0 still 000007：左为处理前，右为降噪后](images/cam0_still_000007_in_orig-dn.jpg)

#### IMG_0012

![IMG 0012：左为处理前，右为降噪后](images/IMG_0012_orig-dn.jpg)

#### IMG_0018

![IMG 0018：左为处理前，右为降噪后](images/IMG_0018_orig-dn.jpg)

#### IMG_0019

![IMG 0019：左为处理前，右为降噪后](images/IMG_0019_orig-dn.jpg)

### 实拍图像

#### grren55_long_f0

![grren55 long f0：左为处理前，右为降噪后](images/grren55_long_f0_orig-dn.jpg)

#### low_low_long_f0

![low low long f0：左为处理前，右为降噪后](images/low_low_long_f0_orig-dn.jpg)
