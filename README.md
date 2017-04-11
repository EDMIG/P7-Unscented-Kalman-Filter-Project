# Unscented Kalman Filter Project Starter Code
Self-Driving Car Engineer Nanodegree Program

Project results:

1. data/sample-laser-radar-measurement-data-1.txt

 RMSE : 0.0813, 0.0886, 0.606, 0.586

2. data/sample-laser-radar-measurement-data-2.txt

 RMSE : 0.177, 0.192, 0.238, 0.297
---

## Dependencies

* cmake >= v3.5
* make >= v4.1
* gcc/g++ >= v5.4

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./UnscentedKF path/to/input.txt path/to/output.txt`. You can find
   some sample inputs in 'data/'.
    - eg. `./UnscentedKF ../data/sample-laser-radar-measurement-data-1.txt output.txt`
5. To force using only Radar or Laser set use_laser_=false or use_radar_=false in src/ukf.cpp accordingly. And re-build project.

## Editor Settings

We've purposefully kept editor configuration files out of this repo in order to
keep it as simple and environment agnostic as possible. However, we recommend
using the following settings:

* indent using spaces
* set tab width to 2 spaces (keeps the matrices in source code aligned)

## Code Style

Please stick to [Google's C++ style guide](https://google.github.io/styleguide/cppguide.html) as much as possible.

## Generating Additional Data

This is optional!

If you'd like to generate your own radar and lidar data, see the
[utilities repo](https://github.com/udacity/CarND-Mercedes-SF-Utilities) for
Matlab scripts that can generate additional data.

## Project Instructions and Rubric

This information is only accessible by people who are already enrolled in Term 2
of CarND. If you are enrolled, see [the project page](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/0949fca6-b379-42af-a919-ee50aa304e6a/lessons/c3eb3583-17b2-4d83-abf7-d852ae1b9fff/concepts/4d0420af-0527-4c9f-a5cd-56ee0fe4f09e)
for instructions and the project rubric.


## Kalman Filter Consistency check - Normalized Innovation Parameter (NIS)

For every step we calculate measurement prediction zk+1 and covoriance matrix Sk+1 (elipse around mean value) then we receive actual measurement zk+1. We can check consistency by finding wether zk+1 measurement is in our Sk+1 eliplse or is it too close to our predicted mean.

- If zk+1 measurement is outside elipse (Sk+1) Kalman Filter prediction is not consistent or in other words Kalman Filter underestimates uncertainty of predicted measurement. KF estimation is less precise as it should be.

- If zk+1 measurement is inside elipse (Sk+1) Kalman Filter prediction is not consistent too,- Kalman Filter overestimate uncertainity of predicted measurement. KF estimation is more precise as it should be.

By calculating NIS we can check consistency - if zk+1 measurement and zk+1 predictions are just right.

$$\epsilon = (z_{k+1} - z_{k+1|k})^T \cdot S^{-1}_{k+1|k} \cdot (z_{k+1} - z_{k+1|k})$$

NIS is difference between predicted measurement and actual measurement. Normalized means that it in to relation with covariance matrix.

NIS value for RADAR must be under 7.815 for 95% of measurement and for LIDAR it must be 5.991 for 95% of measurement. This comes from [Chi Squared distribution](https://en.wikipedia.org/wiki/Chi-squared_distribution).

So if NIS values are greater than KF underestimates uncertainity in system and if NIS values are lower that means thtat KF overestimates uncertainity in system.

[Resulting plots](plots.html)

---

---
## PROJECT DESCRIPTION

The project "unscented Kalman filter" is based on the same structure as the extended Kalman filter.
It uses a main file that calls a function called ProcessMeasurement. Anything important happens in this function. The function is part of the class ukf.

### C++ QUIZZES
The quizzes including the solutions of them are included in the file ukf.cpp. They are individual functions, which don't need any special environment. The solution of the quizzes are given here and also the expected results.
The quizzes can easily evaluated: if every value of the student solution (vectors and matrices) differs less than 0.001 from the original solution, the quizz is passed, otherwise failed.

### PROJECT PASSING CRITERIA
There are several criteria that must be fulfilled to pass the project.

- The overall processing chain (prediction, laser update or radar update depending on measurement type) must be correct.
- The student is not allowed to use values from the future to reason about the current state.
- It must be possible to run the project in three different modes: considering laser only, with considering radar only, or with using both sensors.
- For every mode, the overall RMSE (2d position only) may not be more than 10% increased to what the original solution is able to reach (this number depends on the individual measurement sequence)
- The RMSE of laser AND radar must be lower than radar only or laser only
- The NIS of radar measurements must be between 0.35 and 7.81 in at least 80% of all radar update steps.

### PROJECT GRADING
- I recommend a hall of fame for the lowest overall RMSE using laser AND radar.
- I recommend to ask students to improve the initialization procedure and evaluate the RMSE during the first 20 steps.
