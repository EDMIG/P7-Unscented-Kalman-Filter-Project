#include <iostream>
#include "ukf.h"
#include <math.h>

UKF::UKF() {
    //TODO Auto-generated constructor stub
    Init();
}

UKF::~UKF() {
    //TODO Auto-generated destructor stub
}

void UKF::Init() {

}


/*******************************************************************************
* Programming assignment functions:
*******************************************************************************/

void UKF::SigmaPointPrediction(MatrixXd* Xsig_out) {

    //set state dimension
    int n_x = 5;

    //set augmented dimension
    int n_aug = 7;

    // Transition vector
    VectorXd T = VectorXd(5);
    // Noise vector
    VectorXd N = VectorXd(5);

    //create example sigma point matrix
    MatrixXd Xsig_aug = MatrixXd(n_aug, 2 * n_aug + 1);
    Xsig_aug <<
        5.7441,    5.85768,     5.7441,     5.7441,     5.7441,     5.7441,     5.7441,     5.7441,     5.63052,     5.7441,     5.7441,     5.7441,     5.7441,     5.7441,     5.7441,
            1.38,    1.34566,    1.52806,         1.38,         1.38,         1.38,         1.38,         1.38,     1.41434,    1.23194,         1.38,         1.38,         1.38,         1.38,         1.38,
        2.2049,    2.28414,    2.24557,    2.29582,     2.2049,     2.2049,     2.2049,     2.2049,     2.12566,    2.16423,    2.11398,     2.2049,     2.2049,     2.2049,     2.2049,
        0.5015,    0.44339, 0.631886, 0.516923, 0.595227,     0.5015,     0.5015,     0.5015,     0.55961, 0.371114, 0.486077, 0.407773,     0.5015,     0.5015,     0.5015,
        0.3528, 0.299973, 0.462123, 0.376339,    0.48417, 0.418721,     0.3528,     0.3528,    0.405627, 0.243477, 0.329261,    0.22143, 0.286879,     0.3528,     0.3528,
                 0,                0,                0,                0,                0,                0,    0.34641,                0,                 0,                0,                0,                0,                0, -0.34641,                0,
                 0,                0,                0,                0,                0,                0,                0,    0.34641,                 0,                0,                0,                0,                0,                0, -0.34641;

    //create matrix with predicted sigma points as columns
    MatrixXd Xsig_pred = MatrixXd(n_x, 2 * n_aug + 1);

    double delta_t = 0.1; //time diff in sec
/*******************************************************************************
 * Student part begin
 ******************************************************************************/

    //predict sigma points
    //avoid division by zero
    //write predicted sigma points into right column
    for (int colnr=0; colnr < 2 * n_aug + 1; colnr++) {
        VectorXd xk_aug = Xsig_aug.col(colnr);
        double vk = xk_aug(2);
        double yawk = xk_aug(3);
        double yawdk = xk_aug(4);
        double nu_a = xk_aug(5);
        double nu_yawdd = xk_aug(6);

        N << 0.5 * delta_t * delta_t * cos(yawk) * nu_a,
             0.5 * delta_t * delta_t * sin(yawk) * nu_a,
             delta_t * nu_a,
             0.5 * delta_t * delta_t * nu_yawdd,
             delta_t * nu_yawdd;

        std::cout << yawk << '\n';
        if (fabs(yawdk) > 0.001) {
            T << vk / yawdk * (sin(yawk + yawdk * delta_t) - sin(yawk)),
                 vk / yawdk * (cos(yawk) - cos(yawk + yawdk * delta_t)),
                 0,
                 yawdk * delta_t,
                 0;
        } else {
            T << vk * cos(yawk) * delta_t,
                 vk * sin(yawk) * delta_t,
                 0,
                 0,
                 0;
        }

        Xsig_pred.col(colnr) = xk_aug.head(5) + T + N;
    }


/*******************************************************************************
 * Student part end
 ******************************************************************************/

    //print result
    std::cout << "Xsig_pred = " << std::endl << Xsig_pred << std::endl;

    //write result
    *Xsig_out = Xsig_pred;

}
