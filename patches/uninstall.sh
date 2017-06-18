echo $1
rootdirectory="$PWD"
# ---------------------------------

dirs="bionic frameworks/av frameworks/base system/core"

for dir in $dirs ; do
	cd $rootdirectory
	#cd $dir
	echo "Reverting $dir patches..."
	#git apply --reverse $rootdirectory/device/elephone/p9000/patches/$dir/*.patch
	repo sync $dir
	echo " "
done

# -----------------------------------
echo "Changing to build directory..."
cd $rootdirectory