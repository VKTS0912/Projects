# Soft Gripper Grasping Objects

This is the codebase for training soft grippers to grasp different objects in simulation
 

## Description

Soft grippers are an emerging technology in robotic manipulation, offering a gentle and adaptable approach to grasping objects of various shapes, sizes, and fragilities. Unlike rigid grippers, soft grippers utilize flexible materials and compliant mechanisms, allowing them to conform to the surface of objects and apply uniform pressure without causing damage. This capability makes them ideal for applications in delicate tasks such as handling food, medical supplies, or other sensitive items.

However, training soft grippers to perform precise and reliable grasping tasks presents significant challenges. Traditional control methods often struggle to accommodate the complex dynamics and high degrees of freedom inherent in soft robotic systems. To address these challenges, the teacher-student paradigm has emerged as a powerful framework for training soft grippers effectively.

Such a two-stage teacher-student training paradigm, where first a control policy is trained via Reinforcement Learning with full state information (teacher) and then a second student policy trained via supervised learning to mimic the teacher has been successfully used for many applications. For the grasping task of this project, the idea is to train the teacher policy using deep RL with privileged state information that can be extracted in simulation, and after that, a student policy can be trained to imitate the teacher using sensory inputs from the camera.

However, a significant challenge in robotic learning is the sim-to-real gap, the discrepancy between simulated environments and real-world conditions. While simulations provide a controlled and cost-effective platform for training robotic policies, they often fail to capture all the nuances of the physical world. Differences in sensor noise, friction, material properties, and dynamic interactions can lead to performance degradation when transferring a policy trained in simulation to a real-world robot.

So far, this project focuses on the initial stage of this process: training the teacher policy in simulation. By utilizing advanced simulation tools, this project aims to develop a robust and effective teacher policy that can demonstrate optimal grasping strategies which can generalize to different scale of soft grippers and objects.

## Getting Started

### Dependencies

* [Issac Gym](https://developer.nvidia.com/isaac-gym)
* [IsaacGymEnvs](https://github.com/NVIDIA-Omniverse/IsaacGymEnvs)
* [Wandb](https://wandb.ai/site)

### Installing

* How/where to download your program
* Any modifications needed to be made to files/folders

### Executing program

* How to run the program
* Step-by-step bullets
```
code blocks for commands
```

## Help

Any advise for common problems or issues.
```
command to run if program contains helper info
```

## Authors

Contributors names and contact info

ex. Dominique Pizzie  
ex. [@DomPizzie](https://twitter.com/dompizzie)

## Version History

* 0.2
    * Various bug fixes and optimizations
    * See [commit change]() or See [release history]()
* 0.1
    * Initial Release

## License

This project is licensed under the [NAME HERE] License - see the LICENSE.md file for details

## Acknowledgments

Inspiration, code snippets, etc.
* [awesome-readme](https://github.com/matiassingers/awesome-readme)
* [PurpleBooth](https://gist.github.com/PurpleBooth/109311bb0361f32d87a2)
* [dbader](https://github.com/dbader/readme-template)
* [zenorocha](https://gist.github.com/zenorocha/4526327)
* [fvcproductions](https://gist.github.com/fvcproductions/1bfc2d4aecb01a834b46)