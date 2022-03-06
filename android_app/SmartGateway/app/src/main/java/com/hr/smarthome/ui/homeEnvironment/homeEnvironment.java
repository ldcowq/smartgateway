package com.hr.smarthome.ui.homeEnvironment;

public class homeEnvironment {
    private String Temperature;
    private String Humidity;
    private String Carbon;
    private String Smoke;

    public homeEnvironment() {
    }

    public homeEnvironment(String temperature, String humidity, String carbon, String smoke) {
        Temperature = temperature;
        Humidity = humidity;
        Carbon = carbon;
        Smoke = smoke;
    }

    @Override
    public String toString() {
        return "homeEnvironment{" +
                "Temperature='" + Temperature + '\'' +
                ", Humidity='" + Humidity + '\'' +
                ", Carbon='" + Carbon + '\'' +
                ", Smoke='" + Smoke + '\'' +
                '}';
    }

    public void setTemperature(String temperature) {
        Temperature = temperature;
    }

    public void setHumidity(String humidity) {
        Humidity = humidity;
    }

    public void setCarbon(String carbon) {
        Carbon = carbon;
    }

    public void setSmoke(String smoke) {
        Smoke = smoke;
    }

    public String getTemperature() {
        return Temperature;
    }

    public String getHumidity() {
        return Humidity;
    }

    public String getCarbon() {
        return Carbon;
    }

    public String getSmoke() {
        return Smoke;
    }
}
