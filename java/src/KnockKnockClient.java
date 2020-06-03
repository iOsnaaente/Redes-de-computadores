import java.io.*;
import java.net.*;

public class KnockKnockClient {
    public static void main(String[] args) throws IOException {

        Socket kkSocket = null;
        PrintStream out = null;
        DataInputStream in = null;

        try {
            kkSocket = new Socket("10.3.141.231", 4444);
            out = new PrintStream(kkSocket.getOutputStream());
            in = new DataInputStream(kkSocket.getInputStream());
            
        } catch (UnknownHostException e) {
            System.err.println("Don't know about host: liplop.");
	    System.exit(1);
            
        } catch (IOException e) {
            System.err.println("Couldn't get I/O for the connection to: taranis.");
	    System.exit(1);
        }

        DataInputStream stdIn = new DataInputStream(System.in);
        String fromServer;
        String fromUser;

	while ((fromServer = in.readLine()) != null) {
	    System.out.println("Server: " + fromServer);
	    if (fromServer.equals("Bye."))
		break;

            fromUser = stdIn.readLine();
            
            if (fromUser != null) {
                System.out.println("Client: " + fromUser);
                out.println(fromUser);
            }
	}

	out.close();
	in.close();
	stdIn.close();
	kkSocket.close();
    }
}
