## Requirement
[platformio](https://docs.platformio.org/en/latest/core/installation.html) is required, which can be installed by:
```sh
python3 -c "$(curl -fsSL https://raw.githubusercontent.com/platformio/platformio/develop/scripts/get-platformio.py)"
export PATH=$PATH:~/.platformio/penv/bin
```
## Installation 
Ordinal package installation from source 
```sh
mkdir ~/catkin_ws/src -p  # or whatever your ws
cd ~/catkin_ws/src
git clone https://github.com/HiroIshida/dual_sensor
rosdep install --from-paths dual_sensor --ignore-src -r -y

cd ~/catkin_ws/ && catkin build 
echo "source ~/catkin_ws/devel/setup.bash" >> ~/.bashrc && exec bash # only if you need
```

Import ros and hardware libraries into `lib`
```sh
cd ~/catkin_ws/src/dual_sensor/lib
rosrun rosserial_arduino make_libraries.py .
git clone https://github.com/HiroIshida/SparkFun_LPS25HB_Arduino_Library.git  
```

Build:
```sh
cd ~/catkin_ws/src/dual_sensor/
platformio run
#platformio run --target upload # this command will upload the hex to your bord also
```
