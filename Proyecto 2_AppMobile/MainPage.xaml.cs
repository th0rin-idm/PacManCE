using System;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.Threading.Tasks;
using Xamarin.Essentials;
using Xamarin.Forms;
using System.Linq;
using System.Net.WebSockets;

namespace Proyecto_2_AppMobile
{
    public partial class MainPage : ContentPage
    {
        private const int PortNumber = 5001;
        private UdpClient _udpClient;
        private Socket socket;
        private IPAddress ipAddress;
        public MainPage()
        {
            InitializeComponent();
            var iPAddress = Dns.GetHostEntry(Dns.GetHostName()).AddressList.FirstOrDefault(ip => ip.AddressFamily == AddressFamily.InterNetwork)?.ToString();
            AddressIP.Text = $"La aplicacion mobile esta en la IP: {iPAddress}";
            ipAddress = IPAddress.Parse("192.168.70.47");  //aqui tiene que ir la ip de donde esta funcionando la app c++ ipconfig windows ,ifconfig linux/macos 
            IPEndPoint endpoint= new IPEndPoint(ipAddress, PortNumber);
            Socket socket=new Socket(AddressFamily.InterNetwork,SocketType.Stream,ProtocolType.Tcp);
            socket.Connect(endpoint);
            
            // Inicializar el cliente UDP
            //_udpClient = new UdpClient(PortNumber);
            _ = StartListening();
        }

        private async Task StartListening()
        {
            while (true)
            {
                try
                {
                    // Recibir datos desde el cliente
                    //var result = await _udpClient.ReceiveAsync();
                    byte[] buffer = new byte[1024];
                    var bytesRead= socket.Receive(buffer);
                    var data = Encoding.ASCII.GetString(buffer,0,bytesRead);

                    // Mostrar los datos en la interfaz de usuario
                    var dataItems = data.Split(',');
                    var level = int.Parse(dataItems[0]);
                    var score = int.Parse(dataItems[1]);
                    var life = int.Parse(dataItems[2]);

                    Device.BeginInvokeOnMainThread(() =>
                    {
                        lblLevel.Text = $"Nivel: {level}";
                        lblScore.Text = $"Puntaje: {score}";
                        lblLife.Text = $"Vida restante: {life}";
                    });
                }
                catch (Exception ex)
                {
                    Console.WriteLine($"Error: {ex.Message}");
                }
            }
        }
        private void ConnectButton_Clicked(object sender, EventArgs e)
        {
            // Obtener la dirección IP del servidor desde el Entry
            var ipString = ipEntry.Text;
            if (!IPAddress.TryParse(ipString, out ipAddress))
            {
                // La dirección IP ingresada no es válida
                DisplayAlert("Error", "La dirección IP ingresada no es válida.", "OK");
                return;
            }

            // Conectar al servidor utilizando la dirección IP
            var endPoint = new IPEndPoint(ipAddress, 12345);
            socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            socket.Connect(endPoint);
        }

        protected override void OnAppearing()
        {
            base.OnAppearing();
            Gyroscope.ReadingChanged += Gyroscope_ReadingChanged;
            Gyroscope.Start(SensorSpeed.Game);
        }

        protected override void OnDisappearing()
        {
            base.OnDisappearing();
            Gyroscope.Stop();
            Gyroscope.ReadingChanged -= Gyroscope_ReadingChanged;
        }

        private void Gyroscope_ReadingChanged(object sender, GyroscopeChangedEventArgs e)
        {
            var gyroData = e.Reading;
            // Enviar datos del giroscopio al servidor
            var gyroDataString = $"{gyroData.AngularVelocity.X},{gyroData.AngularVelocity.Y},{gyroData.AngularVelocity.Z}";
            var data = Encoding.ASCII.GetBytes(gyroDataString);
            var client = new UdpClient();
            Address.Text = $"La aplicacion mobile esta en la IP: {ipAddress}";
            client.SendAsync(data, data.Length, new IPEndPoint(IPAddress.Broadcast, PortNumber));
            socket.Send(data);

        }
    }
}
