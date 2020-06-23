./master 1 \
../input/sample_2/target_file $@ & \
./slave 1 \
../output/sample_2/$@ $@ 127.0.0.1
