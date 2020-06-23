./master 10 \
../input/sample_1/target_file_1 \
../input/sample_1/target_file_2 \
../input/sample_1/target_file_3 \
../input/sample_1/target_file_4 \
../input/sample_1/target_file_5 \
../input/sample_1/target_file_6 \
../input/sample_1/target_file_7 \
../input/sample_1/target_file_8 \
../input/sample_1/target_file_9 \
../input/sample_1/target_file_10 $@ & \
./slave 10 \
../output/sample_1/$@_1 \
../output/sample_1/$@_2 \
../output/sample_1/$@_3 \
../output/sample_1/$@_4 \
../output/sample_1/$@_5 \
../output/sample_1/$@_6 \
../output/sample_1/$@_7 \
../output/sample_1/$@_8 \
../output/sample_1/$@_9 \
../output/sample_1/$@_10 $@ 127.0.0.1
