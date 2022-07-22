import java.io.IOException;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;

public class main {
    
    private static HttpURLConnection connection;
    
    public static void main(String[] args) {

        try {
            HttpRequest request = HttpRequest.newBuilder()
                    .uri(URI.create("https://mdblist.p.rapidapi.com/?s=jaws"))
                    .header("X-RapidAPI-Key", "cee54a15cdmsh111590b419bfebcp182fd4jsnf2c5965ba2dc")
                    .header("X-RapidAPI-Host", "mdblist.p.rapidapi.com")
                    .method("GET", HttpRequest.BodyPublishers.noBody())
                    .build();
            HttpResponse<String> response = HttpClient.newHttpClient().send(request, HttpResponse.BodyHandlers.ofString());
            System.out.println(response.body());

            // Request setup

        } catch (MalformedURLException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

    }
}
