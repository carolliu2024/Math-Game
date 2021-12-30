#include "model.hxx"
#include <catch.hxx>

// We'll use this same game config throughout.
Game_config const config;

///
/// MATH GAME TESTS
///
// 1. Arithmetic questions should appear in blocks starting from the top of the screen,
// and slowly fall towards the bottom of the screen.
TEST_CASE("Spec 1")
{
    Model m(config);
    //Check: blocks appear at the top of the screen, y-coord = 0
    //Check that its y-coord = 0
    CHECK(m.block_.coord.y == 0);
    m.on_frame(2);

    //Check: Blocks fall toward the bottom of the screen.
    //x coordinate increases.
    m.on_frame(1);
    CHECK(m.block_.coord.y > 0);
}

//2. Over time, the questions should fall down faster, and the questions
// increase in difficulty (e.g. single digit arithmetic to double digit
// arithmetic).

TEST_CASE("Spec 2: Increase difficulty")
{
    Model m(config);
    Player p = Player();
    //Check: increase in difficulty for blocks
    //Set num of L1 questions correct to 9, check still at L1
    p.num_l1_correct = 9;
    CHECK_FALSE(p.pass_l1());
    //Check single-digit arithmetic
    m.on_frame(2.5);
    CHECK(((m.block_.q_num1.length() == 1) && (m.block_.q_num2.length() == 1)));

    p.num_l1_correct = 10;
    m.on_frame(1000); //Blocks should now have L2 questions after 10 L1 correct
    CHECK(p.pass_l1()); //Check L1 passed
    //Check increase in difficulty (single to double-digit arithmetic)
    int s1 = m.block_.q_num1.length();
    int s2 = m.block_.q_num2.length();
    bool s1_L2 = ((s1 >= 1) && (s1 <= 2)); //0 - 99
    bool s2_L2 = ((s2 >= 1) && (s2 <= 2)); //0 - 99
    CHECK((s1_L2 || s2_L2));
}

TEST_CASE("Spec 3: Player destroys block by entering correct answer")
{
    Model m(config);
    float prev_x = m.block_.coord.x;
    m.block_.coord.y = 100;
    m.block_.q_num1 = "1";
    m.block_.q_num2 = "0";
    m.block_.q_op = "+";
    m.block_.q_text = "1+0";
    m.player_input = "1";
    CHECK(m.block_.get_answer() == "1"); //Correct answer
    //"Destroying" a block = repositioning the block for reuse
    // and redefining q_text and q_nums
    m.check_answer(); //Called once player enters correct ans
    CHECK(m.block_.coord.y != 100);
    m.on_frame(0);
    CHECK(m.block_.coord.y == 0); //Check that block is repositioned
    CHECK(m.block_.coord.x != prev_x);
    //Check that q_text is different after destroying
    CHECK(m.block_.q_text != "1+0");
}

//Block with an extra life is attached.
// "Player enters the correct answer, receiving an extra life. Player gets the next 2 questions "
//           "wrong, and the number "
//           "of lives decreases to 1. The next block has a life attached, and "
//           "player enter the correct answer. Number of lives increases to 2. "
//           "Player gets the next two questions wrong, and the game is over."

TEST_CASE("Spec 4: Losing lives and losing game. Also tests gaining lives")
{
    Model m(config);
    //Check player has 3 lives
    CHECK(m.player.lives == 3);
    m.block_.coord.y = m.config.scene_dims.height+1;
    CHECK(m.block_.hits_bottom(m.config)); //touch bottom of screen
    m.on_frame(0);
    //lose a life
    CHECK(m.player.lives == 2);
    m.player.lives = 0; //game should be over when lives = 0
    m.on_frame(0);
    CHECK(m.game_over());
}

TEST_CASE("Spec 7: Score multiplier check")
{
    Model m(config);
    m.block_.q_num1 = "0";
    m.block_.q_num2 = "0";
    m.block_.q_op = "+";
    m.block_.q_text = "0+0";
    m.player_input = "0";
    CHECK(m.block_.get_answer() == m.player_input); //Correct answer
    m.check_answer();
    CHECK(m.player.streak == 1);
    CHECK(m.player.score == 100);


    m.block_.q_text = "1*0";
    m.player_input = "0";
    CHECK(m.block_.get_answer() == m.player_input); //Correct answer
    m.check_answer();
    CHECK(m.player.streak == 2);
    CHECK(m.player.score == 200);

    m.block_.q_text = "0/1";
    m.player_input = "0";
    CHECK(m.block_.get_answer() == m.player_input); //Correct answer
    m.check_answer();
    CHECK(m.player.streak == 3);
    CHECK(m.player.score == 310);
}
