#include <gtest/gtest.h>


extern "C" {
#include "bankomat.h"
}

class AtmTest : public testing::Test {
protected:
	void SetUp() override {
		//game_initialize();	/* Without this the Tests could break*/
	}
};

TEST_F(AtmTest,WhenWithdrawWithInvalidAccountShouldFail){
    //ARRANGE

    //ACT
    Withdraw_Status status = atmWithdraw("AAA111223",100);

    //ASSERT
    ASSERT_EQ(status,  Withdraw_Status_No_Such_Account);
}


