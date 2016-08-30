/*
 * gtest_zmp.cpp
 *
 *  Created on: May 23, 2014
 *      Author: awinkler
 */

#include <xpp/zmp/zmp_constraint_builder.h>
#include <xpp/zmp/motion_factory.h>
#include <gtest/gtest.h>

namespace xpp {
namespace zmp {

using namespace xpp::hyq;
using MatrixXd = Eigen::MatrixXd;
using VectorXd = Eigen::VectorXd;

TEST(ZmpConstraintBuilderTest, JacobianWrtMotion)
{
  auto start_stance = { Foothold( 0.35,  0.3, 0.0, LF),
                        Foothold( 0.35, -0.3, 0.0, RF),
                        Foothold(-0.35,  0.3, 0.0, LH),
                        Foothold(-0.35, -0.3, 0.0, RH)};

  auto steps =        { Foothold( 0.35+0.3,  0.3, 0.0, LF) };

  hyq::SupportPolygonContainer supp_polygons;
  supp_polygons.Init(start_stance, steps, SupportPolygon::GetDefaultMargins());

  auto com_spline = MotionFactory::CreateComMotion(steps.size(), SplineTimes(), false);

  ZmpConstraintBuilder builder;
  builder.Init(com_spline, 0.58);

  builder.spline_structure_->SetCoefficientsZero();

  MatrixXd jac_wrt_motion   = builder.GetJacobianWrtMotion();
  MatrixXd jac_wrt_contacts = builder.GetJacobianWrtContacts();

  // calculate the jacobian numerically
  VectorXd g = builder.GetDistanceToLineMargin(supp_polygons);

  // perturb the coefficients a little



//  footsteps.Init()
//  stability_constraint_builder.CalcJacobians()





}


//class ZmpConstraintTest : public ::testing::Test {
//
//public:
//  typedef ZmpConstraintBuilder::MatVec MatVec;
//  typedef ZmpConstraintBuilder::Vector2d Vector2d;
//  typedef xpp::hyq::SupportPolygon SupportPolygon;
//  typedef xpp::hyq::Foothold Foothold;
//
//protected:
//  virtual void SetUp()
//  {
//    cont_spline_container_.Init(Eigen::Vector2d::Zero(),
//                                Eigen::Vector2d::Zero(),
//                                1,
//                                SplineTimes(t_swing, t_stance_initial));
//
//    zmp_constaint_.Init(cont_spline_container_, walking_height);
//
//    supp_poly_margins[hyq::FRONT] = 0.10;
//    supp_poly_margins[hyq::HIND]  = 0.10;
//    supp_poly_margins[hyq::SIDE]  = 0.10;
//    supp_poly_margins[hyq::DIAG]  = 0.06; // controls sidesway motion 0.8 even better
//  }
//
//  ComSpline6 spline_container_;
//  ComSpline4 cont_spline_container_;
//  double t_stance_initial = 2.0;
//  double t_swing = 0.5;
//  double walking_height = 0.58;
//
//  hyq::MarginValues supp_poly_margins;
//
//  ZmpConstraintBuilder zmp_constaint_;
//};



} // namespace hyq
} // namespace xpp
