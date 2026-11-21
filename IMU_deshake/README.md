# IMU_deshake

基于 **200 Hz IMU** 的实时视频防抖（EIS）演示。

## 演示视频

下方为 30 fps 动图预览（WebP，约 5–10 MB），点击末尾链接可查看原始画质的完整 mp4。

### 三路对比 · sbs3_dj0183_RAW_STAB_0460_200hz

左 **INPUT**（原始） · 中 **OURS**（本算法） · 右 **DJ**（对比方案）

![sbs3_dj0183_RAW_STAB_0460_200hz](sbs3_dj0183_RAW_STAB_0460_200hz.webp)

[▶ 完整 mp4](sbs3_dj0183_RAW_STAB_0460_200hz.mp4)

### 三路对比 · sbs3_dj0184_RAW_STAB_0461_200hz

左 **INPUT**（原始） · 中 **OURS**（本算法） · 右 **DJ**（对比方案）

![sbs3_dj0184_RAW_STAB_0461_200hz](sbs3_dj0184_RAW_STAB_0461_200hz.webp)

[▶ 完整 mp4](sbs3_dj0184_RAW_STAB_0461_200hz.mp4)

### 双路对比 · sbs_mv7_RAW_STAB_off6

左 **INPUT**（原始） · 右 **OURS**（本算法）；纯效果展示，无第三方对比

![sbs_mv7_RAW_STAB_off6](sbs_mv7_RAW_STAB_off6.webp)

[▶ 完整 mp4](sbs_mv7_RAW_STAB_off6.mp4)

画面上的标注已直接叠加在视频左上角，便于逐帧对比。前两个视频含大疆（DJ）对比，`sbs_mv7` 仅用于展示本算法效果。

## 效果

在手持抖动视频上：

- 2–10 Hz 抖动能量平均降低 **99.9%**
- jerk（加加速度）降低 **98.5%**
- 相机角速度 RMS 从 **33°/s 降至 12.7°/s（−62%）**
- 同时保留 **~100% 的低频有意运动**

## 性能

Intel Core i5-13500，单核（固定同一逻辑核）：

| 指标 | 结果 |
|------|------|
| 单帧耗时（不含 GDC） | **0.108 ms/帧** |
| 测试数据 | 1920×1080 @ 30 fps，8191 帧 |
| 测试方法 | 固定单核，预热 3 s，连续测试 15 次取最快值 |

> 说明：该耗时包含 IMU 滤波（ESKF）、逐帧轨迹规划与 GDC 矩阵生成；不含 GDC 像素重采样（由硬件完成）。
