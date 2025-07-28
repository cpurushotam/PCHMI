# Version: 1.0
#find /media/ -name UIController -type f | xargs cp -t /home/jerry0621/opt
#cd /home/jerry0621/opt/ && ./UIController
kill -9 $(ps -e|grep UIController | awk '{print $1}')
find /media/ -name UIController -type f | xargs cp -t /opt/UIController/bin
cd /opt/UIController/bin && ./UIController

# Version: 1.1
#SOURCE_FILE=$(find /media/ -name UIController -type f | xargs)
#SOURCE_FILE=$(find /media/ -name WES7P_PCM9376_V5.1.2.zip -type f | xargs)
#echo $SOURCE_FILE
#TARGET_DIR="/home/jerry0621/opt/UIController"
#cp -r "$SOURCE_FILE" "$TARGET_DIR" &
#compute_percent()
#{
#     SOURCE_SIZE=$(/usr/bin/du -s ${1} | awk '{print $1}')
#     TARGET_SIZE=$(/usr/bin/du -s ${2} | awk '{print $1}')
#     let i=$TARGET_SIZE*100/$SOURCE_SIZE
#     return $i
#}
#compute_percent ${SOURCE_FILE} ${TARGET_DIR}
#while [ ${i} -lt 100 ]
#do
#compute_percent ${SOURCE_FILE} ${TARGET_DIR}
#echo $i
#sleep 0.5
#done
#cd /home/jerry0621/opt/ && ./UIController
