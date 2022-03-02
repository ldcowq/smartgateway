package com.hr.smarthome.ui.home;

public class FireJavaBean {

    private String angle;
    private String batpt;
    private String watergage;
    private String id;
    private String create_at;
    private String update_at;
    private String longitude;
    private String latitude;
    private String eqid;

    public String getAngle() {
        return angle;
    }

    public void setAngle(String angle) {
        this.angle = angle;
    }

    public String getBatpt() {
        return batpt;
    }

    public void setBatpt(String batpt) {
        this.batpt = batpt;
    }

    public String getWatergage() {
        return watergage;
    }

    public void setWatergage(String watergage) {
        this.watergage = watergage;
    }

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getCreate_at() {
        return create_at;
    }

    public void setCreate_at(String create_at) {
        this.create_at = create_at;
    }

    public String getUpdate_at() {
        return update_at;
    }

    public void setUpdate_at(String update_at) {
        this.update_at = update_at;
    }

    public String getLongitude() {
        return longitude;
    }

    public void setLongitude(String longitude) {
        this.longitude = longitude;
    }

    public String getLatitude() {
        return latitude;
    }

    public void setLatitude(String latitude) {
        this.latitude = latitude;
    }

    public String getEqid() {
        return eqid;
    }

    public void setEqid(String eqid) {
        this.eqid = eqid;
    }

    public FireJavaBean() {
    }

    public FireJavaBean(String angle, String batpt, String watergage, String id, String create_at, String update_at, String longitude, String latitude, String eqid) {
        this.angle = angle;
        this.batpt = batpt;
        this.watergage = watergage;
        this.id = id;
        this.create_at = create_at;
        this.update_at = update_at;
        this.longitude = longitude;
        this.latitude = latitude;
        this.eqid = eqid;
    }

    @Override
    public String toString() {
        return "FireJavaBean{" +
                "angle='" + angle + '\'' +
                ", batpt='" + batpt + '\'' +
                ", watergage='" + watergage + '\'' +
                ", id='" + id + '\'' +
                ", create_at='" + create_at + '\'' +
                ", update_at='" + update_at + '\'' +
                ", longitude='" + longitude + '\'' +
                ", latitude='" + latitude + '\'' +
                ", eqid='" + eqid + '\'' +
                '}';
    }
}
