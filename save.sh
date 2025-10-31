#!/bin/bash
git add .
git commit -m "$1"
git push github master
echo "提交完成: $1"
