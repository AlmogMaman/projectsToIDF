using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Threading;
using System.Runtime.InteropServices;




class room
{
    public string Name { get; set; }
    public string Lvl { get; set; }
    public string Count { get; set; }
    public uint Id { get; set; }
}


class statisForGame
{
    public int right { get; set; }
    public int wrong { get; set; }
    public float time { get; set; }
}

namespace client
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private string userName = "";
        private string[] lvls = { "Easy", "Normal", "Hard" };
        private int lvl, Timer, Time, NumQue, CountQue;
        private uint Id, roomId;
        DispatcherTimer dtClockTime;
        DispatcherTimer playersListReq;
        communication com = new communication();


        public MainWindow()
        {
            InitializeComponent();
            dtClockTime = new DispatcherTimer();
            dtClockTime.Tick += dtClockTime_Tick;
            dtClockTime.Interval = new TimeSpan(0, 0, 1);
            dtClockTime.Stop();

            playersListReq = new DispatcherTimer();
            playersListReq.Tick += playersListReqwest;
            playersListReq.Interval = new TimeSpan(0, 0, 5);
            playersListReq.Stop();
            Timer = -1;
        }


        private void Singup_Click(object sender, RoutedEventArgs e)
        {
            char[] BigLatters = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'G', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
            char[] SmallLatters = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'g', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
            char[] nums = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
            string j = "{\"name\":" + newUsername.Text + "\"password\":" + newPassword.Text+"}";
            if (string.IsNullOrEmpty(newUsername.Text))
            {
                //verify and enter username.
                MessageBox.Show("Enter your username.", "Empty", MessageBoxButton.OK, MessageBoxImage.Information);
                txtUsername.Focus();
                return;
            }
            else if (string.IsNullOrEmpty(newPassword.Text))
            {
                MessageBox.Show("Enter your password.", "Empty", MessageBoxButton.OK, MessageBoxImage.Information);
                txtPassword.Focus();
                return;
            }
            else if (newPassword.Text.IndexOfAny(BigLatters) == -1 || newPassword.Text.IndexOfAny(SmallLatters) == -1 || newPassword.Text.IndexOfAny(nums) == -1)
            {
                MessageBox.Show("Illegal password.\nPassword must contain big letter, small letter and number", "Empty", MessageBoxButton.OK, MessageBoxImage.Information);
                txtPassword.Focus();
                return;
            }

            Id = com.Signup(newUsername.Text, newPassword.Text);
            if (Id != 0)
            {

                userName = newUsername.Text;
                Sing_up.Visibility = Visibility.Hidden;
                option.Visibility = Visibility.Visible;
            }
            else
            {
                MessageBox.Show("Error signup\nname is taken", "Empty", MessageBoxButton.OK, MessageBoxImage.Information);
                txtPassword.Focus();
                return;
            }

        }


        private void BtnLoginUser_Click(object sender, RoutedEventArgs e)
        {
            if (string.IsNullOrEmpty(txtUsername.Text))
            {
                MessageBox.Show("Enter your username.", "Empty", MessageBoxButton.OK, MessageBoxImage.Information);
                txtUsername.Focus();
                return;
            }
            else if (string.IsNullOrEmpty(txtPassword.Password))
            {
                MessageBox.Show("Enter your password.", "Empty", MessageBoxButton.OK, MessageBoxImage.Information);
                txtPassword.Focus();
                return;
            }


            Id = com.login(txtUsername.Text, txtPassword.Password);
            if (Id != 0)
            {
                userName = txtUsername.Text;
                start.Visibility = Visibility.Hidden;
                option.Visibility = Visibility.Visible;
            }
            else
            {
                MessageBox.Show("Error login", "Empty", MessageBoxButton.OK, MessageBoxImage.Information);
                txtPassword.Focus();
                return;
            }
        }

        /*
         * the function gets the active rooms from the server
        */

        private void get_rooms(object sender, RoutedEventArgs e)
        {
            option.Visibility = Visibility.Hidden;
            room_list.Visibility = Visibility.Visible;

            listRoomsResponse rooms = com.get_room_list();
            list.Items.Clear();

            unsafe
            {
                listRoomsResponse* r = rooms.next;
                while (r != null)
                {
                    //creates new room and adds it to the rooms list
                    list.Items.Add(new room() { Name = Marshal.PtrToStringAnsi(r->name), Lvl = lvls[r->lvl], Count = r->numOfPlayers + "/" + r->maxNum ,Id = r->id});
                    r = r->next;
                }
            }
        }



        private void join_room(object sender, RoutedEventArgs e)
        {
            //choosing validation
            if(list.SelectedIndex == -1)
            {
                MessageBox.Show("You need to chose a room.", "error", MessageBoxButton.OK, MessageBoxImage.Information);
                txtUsername.Focus();
                return;
            }
            
            room_list.Visibility = Visibility.Hidden;
            room r = (room)list.SelectedItem;
            roomId = r.Id;
            JoinRoomResponse joinRoom = com.join_room(roomId, userName);
            if (joinRoom.enter == 1)
            {
                start_room_loby(r.Name, (int)joinRoom.maxUsers, (int)joinRoom.questionCount, (int)joinRoom.answerTimeout, r.Lvl, false);
            }
            else
            {
                room_list.Visibility = Visibility.Visible;
                MessageBox.Show("The room is full.", "error", MessageBoxButton.OK, MessageBoxImage.Information);
                txtUsername.Focus();
                return;
            }
        }



        private void send_inf(object sender, RoutedEventArgs e)
        {
            int max, num, t;
            //input validations:
            if (string.IsNullOrEmpty(room_name.Text))
            {
                MessageBox.Show("Enter your username.", "Empty", MessageBoxButton.OK, MessageBoxImage.Information);
                txtUsername.Focus();
                return;
            }
            else if (string.IsNullOrEmpty(max_players.Text) || !int.TryParse(max_players.Text, out max) || max <= 0)
            {
                MessageBox.Show("Max number of players could be only a positive number.", "Error", MessageBoxButton.OK, MessageBoxImage.Information);
                txtPassword.Focus();
                return;
            }
            else if (string.IsNullOrEmpty(num_qw.Text) || !int.TryParse(num_qw.Text, out num) || num <= 0) 
            {
                MessageBox.Show("Numger of questions could be only a positive number.", "Error", MessageBoxButton.OK, MessageBoxImage.Information);
                txtPassword.Focus();
                return;
            }
            else if (string.IsNullOrEmpty(time.Text) || !int.TryParse(time.Text, out t) || t <= 0) 
            {
                MessageBox.Show("Time could be only a positive number..", "Error", MessageBoxButton.OK, MessageBoxImage.Information);
                txtPassword.Focus();
                return;
            }
            
            create_room.Visibility = Visibility.Hidden;
            com.create_room(userName, room_name.Text, max, num, Array.BinarySearch(lvls, ((ComboBoxItem)Difficulty.SelectedValue).Content.ToString().Split('\t')[0]), t);
            roomId = Id;
            start_room_loby(room_name.Text, max, num, t, ((ComboBoxItem)Difficulty.SelectedValue).Content.ToString().Split('\t')[0], true);
        }


        private void start_room_loby(string n, int p, int q, int t,string lv,bool admin)
        {
            room_loby.Visibility = Visibility.Visible;
            name.Text = "Room  name: "+n;
            palyers.Text = "Max number of players: " + p;
            questions.Text = "Number of questions: " + q;
            game_time.Text = "Time per question:(sec) " + t;
            dif_lvl.Text = "Difficulty: " + lv;


            playersListReq.Start();
            
            Time = t;
            NumQue = q;
            CountQue = 0;
            if (lv == "Easy")
                lvl = 1;
            else if (lv == "Normal")
                lvl = 2;
            else
                lvl = 3;


            if (admin)
            {
                close.Visibility = Visibility.Visible;
                start_game_btn.Visibility = Visibility.Visible;
                leave_btn.Visibility = Visibility.Hidden;

            }
            else
            {
                close.Visibility = Visibility.Hidden;
                start_game_btn.Visibility = Visibility.Hidden;
                leave_btn.Visibility = Visibility.Visible;
            }
        }

        private void leave_room_loby(object sender, RoutedEventArgs e)
        {
            playersListReq.Stop();

            com.leave_room(roomId, userName, roomId == Id);
            room_loby.Visibility = Visibility.Hidden;
            option.Visibility = Visibility.Visible;
        }

        private void my_status(object sender, RoutedEventArgs e)
        {
            option.Visibility = Visibility.Hidden;
            status_stack.Visibility = Visibility.Visible;
            back_to_loby.Visibility = Visibility.Hidden;
            get_player_inf(userName);
        }

        private void player_status(object sender, RoutedEventArgs e)
        {
            if (players_list.SelectedIndex == -1)
            {
                MessageBox.Show("You need to chose a player.", "error", MessageBoxButton.OK, MessageBoxImage.Information);
                txtUsername.Focus();
                return;
            }
            
            


            room_loby.Visibility = Visibility.Hidden;
            status_stack.Visibility = Visibility.Visible;
            back_to_loby.Visibility = Visibility.Visible;
           
            get_player_inf(players_list.SelectedValue.ToString());
        }


        private void get_player_inf(string name)
        {
            PlayerResultsResponse player = com.get_status(name);
            player_name.Text = "Name: "+name;
            num_games.Text = "Games played: "+ player.gamesPlayed;
            num_win_games.Text = " Win games: "+player.gamesWin;
            right_ans.Text = " Right answers: "+player.correctAnswerCount;
            wrong_ans.Text = " Wrong answers: "+player.wrongAnswerCount;
            avr_ans.Text = " Average time per answer: "+player.averageAnswerTime;
        }

        private void top_players(object sender, RoutedEventArgs e)
        {
            option.Visibility = Visibility.Hidden;
            top.Visibility = Visibility.Visible;
            first.Foreground = Brushes.Black;
            secound.Foreground = Brushes.Black;
            third.Foreground = Brushes.Black;
            you.Foreground = Brushes.Green;
            you.Visibility = Visibility.Visible;


            TopPlayersResponse players = com.get_top_players(userName);
            uint id = players.place;

            first.Text = "1.  " + Marshal.PtrToStringAnsi(players.first);
            secound.Text = "2.  " + Marshal.PtrToStringAnsi(players.secound);
            third.Text = "3.  " + Marshal.PtrToStringAnsi(players.third);

            if (id == 1)
            {
                first.Foreground = Brushes.Green;
                you.Visibility = Visibility.Hidden;
            }
            else if (id == 2)
            {
                secound.Foreground = Brushes.Green;
                you.Visibility = Visibility.Hidden;
            }
            else if (id == 3)
            {
                third.Foreground = Brushes.Green;
                you.Visibility = Visibility.Hidden;
            }
            else
                you.Text = id + ".  " + userName;

        }

        private void back_from_top(object sender, RoutedEventArgs e)
        {
            top.Visibility = Visibility.Hidden;
            option.Visibility = Visibility.Visible;
        }

        private void back_from_status(object sender, RoutedEventArgs e)
        {
            status_stack.Visibility = Visibility.Hidden;
            option.Visibility = Visibility.Visible;
        }

        private void back_to_room_loby(object sender, RoutedEventArgs e)
        {
            status_stack.Visibility = Visibility.Hidden;
            room_loby.Visibility = Visibility.Visible;
        }


        private void back_from_options(object sender, RoutedEventArgs e)
        {
            com.Signout(userName);
            userName = "";
            start.Visibility = Visibility.Visible;
            option.Visibility = Visibility.Hidden;
        }

        private void open_singin(object sender, RoutedEventArgs e)
        {
            start.Visibility = Visibility.Hidden;
            Sing_up.Visibility = Visibility.Visible;
        }

        private void back_to_start(object sender, RoutedEventArgs e)
        {
            Sing_up.Visibility = Visibility.Hidden;
            start.Visibility = Visibility.Visible;
        }

        private void open_create(object sender, RoutedEventArgs e)
        {
            option.Visibility = Visibility.Hidden;
            create_room.Visibility = Visibility.Visible;

        }
        private void back_from_roomList(object sender, RoutedEventArgs e)
        {
            option.Visibility = Visibility.Visible;
            room_list.Visibility = Visibility.Hidden;
        }

        private void back_from_create(object sender, RoutedEventArgs e)
        {
            option.Visibility = Visibility.Visible;
            create_room.Visibility = Visibility.Hidden;
        }

        private void back_to_manu(object sender, RoutedEventArgs e)
        {
            option.Visibility = Visibility.Visible;
            end_game.Visibility = Visibility.Hidden;
        }
        

        private void Exit_Click(object sender, RoutedEventArgs e)
        {
            com.exit(userName);
            this.Close();
        }

        private void close_Click(object sender, System.ComponentModel.CancelEventArgs e)
        {
            com.exit(userName);
        }

        private void start_game(object sender, RoutedEventArgs e)
        {
            room_loby.Visibility = Visibility.Hidden;
            gameplay.Visibility = Visibility.Visible;


            

            if(lvl==1)
            {
                ans4.Visibility = Visibility.Hidden;
                ans3.Visibility = Visibility.Hidden;
            }
            else if(lvl == 2)
            {
                ans4.Visibility = Visibility.Hidden;
                ans3.Visibility = Visibility.Visible;
            }
            else
            {
                ans4.Visibility = Visibility.Visible;
                ans3.Visibility = Visibility.Visible;
            }

            dtClockTime.Start();

            get_que();

        }

        private void playersListReqwest(object sender, EventArgs e)
        {
            usersInRoomResponse users = com.users_in_room(roomId);
            players_list.Items.Clear();
            unsafe
            {
                usersInRoomResponse* r = users.next;
                if (r == null)
                {
                    playersListReq.Stop();

                    MessageBox.Show("Admin closed the room.", "Empty", MessageBoxButton.OK, MessageBoxImage.Information);
                    txtPassword.Focus();
                    
                    
                    room_loby.Visibility = Visibility.Hidden;
                    option.Visibility = Visibility.Visible;
                }
                else
                {
                    while (r != null)
                    {
                        players_list.Items.Add(Marshal.PtrToStringAnsi(r->name));
                        r = r->next;
                    }
                }
            }
        }



        private void dtClockTime_Tick(object sender, EventArgs e)
        {
            lblTime.Text = Timer.ToString();
            Timer--;

            if (Timer == -1)
            {
                CountQue++;
                if (CountQue < NumQue)
                    get_que();
                else
                {
                    dtClockTime.Stop();
                    gameplay.Visibility = Visibility.Hidden;
                    end_game.Visibility = Visibility.Visible;
                }
            }

        }

        void get_que()
        {
            var ans = new List<string>();
            ans.Add("1 First answer ");
            ans.Add("2 Secound room ");
            ans.Add("3  Third room  ");
            ans.Add("4  Fourth room ");

            //get answer

            Timer = Time;
            question.Text = "first question";
            


            ans1.Content = ans[0];
            ans2.Content = ans[1];
            if(lvl>1)
                ans3.Content = ans[2];
            if(lvl>2)
                ans4.Content = ans[3];

            ans1.Foreground = col.Foreground;
            ans2.Foreground = col.Foreground;
            ans3.Foreground = col.Foreground;
            ans4.Foreground = col.Foreground;

            ans1.IsEnabled = true;
            ans2.IsEnabled = true;
            ans3.IsEnabled = true;
            ans4.IsEnabled = true;

        }

        bool check_ans(int num)
        {
            ans1.IsEnabled = false;
            ans2.IsEnabled = false;
            ans3.IsEnabled = false;
            ans4.IsEnabled = false;
            //get right ans
            if (num % 2 == 0)
                return true;
            return false;
        }

        


        private void first_ans(object sender, RoutedEventArgs e)
        {

            if(check_ans(1))
                ans1.Foreground = Brushes.Green;
            else
                ans1.Foreground = Brushes.Red;

        }

        private void secound_ans(object sender, RoutedEventArgs e)
        {
            if (check_ans(2))
                ans2.Foreground = Brushes.Green;
            else
                ans2.Foreground = Brushes.Red;
        }

        private void third_ans(object sender, RoutedEventArgs e)
        {
            if (check_ans(3))
                ans3.Foreground = Brushes.Green;
            else
                ans3.Foreground = Brushes.Red;
        }

        private void fourth_ans(object sender, RoutedEventArgs e)
        {
            if (check_ans(4))
                ans4.Foreground = Brushes.Green;
            else
                ans4.Foreground = Brushes.Red;
        }



        
    }
}