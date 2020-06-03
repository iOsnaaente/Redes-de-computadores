import java.net.*;
import java.io.*;

public class KKMultiServerThread extends Thread {
    private Socket socket = null;

    public KKMultiServerThread(Socket socket) {
        super("KKMultiServerThread");
        this.socket = socket;
    }

    public void run() {

        try {
            DataInputStream in = new DataInputStream(
                                  new BufferedInputStream(socket.getInputStream()));
            PrintStream out = new PrintStream(
                              new BufferedOutputStream(socket.getOutputStream(), 1024), false);

            String inputLine, outputLine;
	    KnockKnockProtocol kkp = new KnockKnockProtocol();

            outputLine = kkp.processInput(null);
            out.println(outputLine);
            out.flush();

            while ((inputLine = in.readLine()) != null) {
                outputLine = kkp.processInput(inputLine);
                out.println(outputLine);
                out.flush();
                if (outputLine.equals("Bye"))
                    break;
            }
            out.close();
            in.close();
            socket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
