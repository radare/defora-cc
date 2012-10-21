#!/bin/sh
#
# sh gitclonedir.sh DeforaOS/DeforaOS/System/src/libSystem/
#
#DIR=`echo "$1" | cut -d / -f 2-`
DIR="`echo $1 |cut -d / -f 2-`"
echo $DIR
if [ -z "$DIR" ]; then
	echo "Usage: sh gitclonedir.sh DeforaOS/DeforaOS/System/src/libSystem"
	exit 1
fi
OUT=$(basename ${DIR})
PRE=$(dirname ${DIR})

PRE=$(echo ${DIR}|cut -d / -f 2-)
echo DIR=$DIR
echo OUT=$OUT
echo PRE=$PRE

if [ ! -d "DeforaOS" ]; then
	git clone git://github.com/khorben/DeforaOS.git
fi

if [ ! -d "DeforaOS/${DIR}" ]; then
	echo "Direcotyr not found"
	exit 1
fi

cd DeforaOS
git commit -a -m "oops"
cd ..

rm -rf ${OUT}
git clone DeforaOS ${OUT}
cd ${OUT}

#git filter-branch --subdirectory-filter DeforaOS/System/src/libSystem/ -- --all 
git filter-branch --subdirectory-filter ${DIR} -- --all

# Fix commiters
git filter-branch -f --env-filter '

an="$GIT_AUTHOR_NAME"
am="$GIT_AUTHOR_EMAIL"
cn="$GIT_COMMITTER_NAME"
cm="$GIT_COMMITTER_EMAIL"

if [ "" = "$GIT_COMMITTER_EMAIL" ]; then
	cn="Pierre Pronchery"
	cm="khorben@defora.org"
fi
if [ "" = "$GIT_AUTHOR_EMAIL" ]; then
	an="Pierre Pronchery"
	am="khorben@defora.org"
fi

export GIT_AUTHOR_NAME="$an"
export GIT_AUTHOR_EMAIL="$am"
export GIT_COMMITTER_NAME="$cn"
export GIT_COMMITTER_EMAIL="$cm"
'
git reflog expire --expire=now --all
git gc --prune=now --aggressive
git repack -ad
