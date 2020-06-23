./master 5 \
../input/sample_3/target_file_1 \
../input/sample_3/target_file_2 \
../input/sample_3/target_file_3 \
../input/sample_3/target_file_4 \
../input/sample_3/target_file_5 $@ & \
./slave 5 \
../output/sample_3/$@_1 \
../output/sample_3/$@_2 \
../output/sample_3/$@_3 \
../output/sample_3/$@_4 \
../output/sample_3/$@_5 $@ 127.0.0.1
