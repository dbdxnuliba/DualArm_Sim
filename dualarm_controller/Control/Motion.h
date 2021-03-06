/*
 * Motion.h
 *
 *  Created on: 2019. 8. 1.
 *      Author: Administrator
 */

#ifndef MOTION_H_
#define MOTION_H_

#include "Trajectory.h"
#include "../KDL/SerialManipulator.h"
#include "../KDL/LieOperator.h"
#include "slerpHandler.h"

namespace HYUControl {

class Motion {
public:
	Motion();
	explicit Motion(std::shared_ptr<SerialManipulator> Manipulator);
	virtual ~Motion();

	uint16_t JointMotion(VectorXd &dq, VectorXd &dqdot, VectorXd &dqddot, VectorXd &_Target, const VectorXd &q, const VectorXd &qdot, double &_Time, unsigned char &_StatusWord, unsigned char &_MotionType);
	uint16_t TaskMotion( Cartesiand *_dx, VectorXd &_dxdot, VectorXd &_dxddot, VectorXd _Target, const VectorXd &x, const VectorXd &qdot, double &_Time, unsigned char &_StatusWord, unsigned char &_MotionType );
    uint16_t TaskMotion2( Quaterniond &_q_R, Quaterniond &_q_L, Vector3d &_TargetPos_Linear_R, Vector3d &_TargetPos_Linear_L, Vector3d &_TargetPos_Linear_R2, Vector3d &_TargetPos_Linear_L2,
                          Quaterniond &_vive_dR_R, Quaterniond &_vive_dR_L, Vector3d &_vive_dP_R, Vector3d &_vive_dP_L, Vector3d &_vive_dP_R2, Vector3d &_vive_dP_L2,
                          VectorXd &_dtwist, VectorXd &_dtwist2, VectorXd &_dxdot,VectorXd &_dxdot2, VectorXd &_dxddot,
                          VectorXd _Target, const VectorXd &x, const VectorXd &qdot,
                          double &_Time, unsigned char &_StatusWord, unsigned char &_MotionType );
private:

	Eigen::VectorXd e, edot;
	Eigen::VectorXd TargetPos, TargetPos_p;

	Eigen::MatrixXd omega;



	Eigen::VectorXd xdot, xdot2;
	Eigen::VectorXd TargetPosTask, TargetPosTask_p;
	Eigen::VectorXd TargetPos_Linear;
    Eigen::Vector3d TargetPos_Linear_R, TargetPos_Linear_L,TargetPos_Linear_R2, TargetPos_Linear_L2, vive_dP_R, vive_dP_L;

    Cartesiand x[2];
	Eigen::VectorXd _dx_tmp, _dxdot_tmp, _dxddot_tmp, dtwist, dtwist2;
	Eigen::VectorXd _x_tmp, _xdot_tmp;
	Eigen::MatrixXd AJacobian;
    Eigen::MatrixXd AJacobian2;


    Eigen::Quaterniond r, r1, q_R, q_L, vive_dR_R, vive_dR_L, vive_dR_R2, vive_dR_L2;
	Eigen::Vector3d rdot, rddot, rdot1, rddot1;

	Eigen::VectorXd start_pos;

    std::shared_ptr<SerialManipulator> pManipulator;

	Trajectory JointPoly5th;
	Trajectory TaskPoly5th;

	slerpHandler slerp_ori[2];

	int MotionProcess;
	int NewTarget=0;

	uint16_t MotionCommand=0;
	uint16_t MotionCommand_p=0;
	uint16_t MotionCommandTask=0;
	uint16_t MotionCommandTask_p=0;

	double MotionInitTime=0;
	double TrajectoryTime=0;

	double init_time=0;

	int TotalDoF;
	int TotalChain;

	double _T=0;
	double _omega=0;
	double _amp=0;

	int MotionCounter=0;

};

} /* namespace hyuCtrl */

#endif /* MOTION_H_ */
