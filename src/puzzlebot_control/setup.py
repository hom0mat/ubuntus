from setuptools import find_packages, setup
import os
from glob import glob

package_name = 'puzzlebot_control'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        (os.path.join('share', package_name, 'launch'), glob(os.path.join('launch', '*launch.[pxy][yma]*'))),
        (os.path.join('share', package_name, 'config'), glob(os.path.join('config', '*.[yma]*'))),
        (os.path.join('share', package_name, 'rviz'), glob(os.path.join('rviz', '*.rviz'))),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='Mario Martinez',
    maintainer_email='mario.mtz@manchester-robotics.com',
    description='Puzzlebot Control',
    license='Apache-2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'open_loop_ctrl = puzzlebot_control.open_loop_ctrl:main',
            'path_gen = puzzlebot_control.path_gen:main',
            'open_ctrl = puzzlebot_control.open_ctrl:main'
        ],
    },
)
