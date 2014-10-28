#!/bin/bash
# For every file in $Target/HelloWorld/mbed compare text files of each target

# Dirs are:  HelloWorld/
#                     ./mbed/
#			   ./TARGET_LPC1768
#			                  ./TARGET_NXP/TARGET_LPC176X
#			                                            ./TARGET_MBED_LPC1768/
#

DirBaseGcc=HelloWorld_gcc_arm_lpc1768/HelloWorld
DirBaseuV=HelloWorld_uvision_lpc1768/HelloWorld
DirSeg2=mbed
DirSeg3=TARGET_LPC1768
DirSeg4=TARGET_NXP/TARGET_LPC176X
DirSeg5=TARGET_MBED_LPC1768


declare -i TextSameFiles=0
declare -i TextDifferentFiles=0
declare -i TotalLines=0
declare -i LineCount=0
declare -i GccUniqFiles=0
declare -i uVUniqFiles=0
declare -i sameFileNameDifferentText=0
for Dir2ndPart in $DirSeg2/ $DirSeg2/$DirSeg3/ $DirSeg2/$DirSeg3/$DirSeg4/ $DirSeg2/$DirSeg3/$DirSeg4/$DirSeg5/ 
do
	for File in `ls $DirBaseGcc/$Dir2ndPart/`
	do
		# Check to see that $File exists in other target's directory:
	if [ -f $DirBaseGcc/$Dir2ndPart/$File ]; then # limit to non-directory files...

		if [ ! -e $DirBaseuV/$Dir2ndPart/$File ]; then # File doesn't exist in uVision target
			printf "Matching File %s not found in uvision directory!\n" $File
			GccUniqFiles=$GccUniqFiles+1

		elif diff $DirBaseGcc/$Dir2ndPart/$File $DirBaseuV/$Dir2ndPart/$File  
		   # Both files identical
		   then
			TextSameFiles=$TextSameFiles+1
			LineCount=`wc -l $DirBaseGcc/$Dir2ndPart/$File |  awk '{print $1}'`
			# printf "File %s is the same for both targets with %s lines\n" $File $LineCount
			TotalLines=$TotalLines+$LineCount
			# printf "Running Lines is: %s\n" $TotalLines
		
		else # Files are different
			printf "File %s is different for targets!!\n" $File
			sameFileNameDifferentText=$sameFileNameDifferentText+1
		fi
	fi
	done
done

# Now check for uV text files that are unique
for Dir2ndPart in $DirSeg2/ $DirSeg2/$DirSeg3/ $DirSeg2/$DirSeg3/$DirSeg4 $DirSeg2/$DirSeg3/$DirSeg4/$DirSeg5/ 
do
	for File in `ls $DirBaseuV/$Dir2ndPart`
	do
		# Check to see that $File exists in other target's directory:
		if [ ! -e $DirBaseGcc/$Dir2ndPart/$File ] && [ -f $DirBaseuV/$Dir2ndPart/$File/ ]; then
			printf "Matching File %s not found in Gcc_ARM directory!\n" $File
			uVUniqFiles=$uVUniqFiles+1;
		fi
	done
done
printf "Total number of %s text files that are identical.\n\n" $TextSameFiles
printf "Total of %s lines in identical text files.\n\n" $TotalLines
printf "Total number of %s text files that are different.\n\n" $TextDifferentFiles
printf "Total number of %s text files unique to GCC_ARM target.\n\n" $GccUniqFiles
printf "Total number of %s text files unique to uVision target.\n\n" $uVUniqFiles
