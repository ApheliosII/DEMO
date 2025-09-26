MINIX := minix-1.7
# MINIX := minix-2.0

run: minix2
	cd minix2 \
	  && ln -s -f images/$(MINIX)-hd-*.img hd.img \
	  && ./runqemu

minix2:
	git clone --depth 1 --single-branch -b master \
	  https://github.com/davidgiven/minix2
	cd minix2 \
	  && ./mkall \
	  && gunzip images/*.gz

.PHONEY: minix2

###
# # 设置默认版本 (取消注释需要使用的版本)
# MINIX_VERSION := minix-1.7
# # MINIX_VERSION := minix-2.0

# # 主运行目标
# run: minix2/hd.img
# 	cd minix2 && ./runqemu

# # 创建软链接并准备环境
# minix2/hd.img: minix2/.prepared
# 	cd minix2 && ln -sf images/$(MINIX_VERSION)-hd-64MB.img hd.img

# # 构建Minix镜像
# minix2/.prepared: minix2
# 	cd minix2 && \
# 		./mkall && \
# 		gunzip -f images/*.gz && \
# 		touch .prepared

# # 克隆仓库
# minix2:
# 	git clone --depth 1 --single-branch -b master \
# 		https://github.com/davidgiven/minix2

# # 清理构建产物
# clean:
# 	rm -rf minix2

# .PHONY: run clean