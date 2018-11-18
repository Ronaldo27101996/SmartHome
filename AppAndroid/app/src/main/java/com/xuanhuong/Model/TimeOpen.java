package com.xuanhuong.Model;

import java.io.Serializable;

/**
 * Created by CR7 on 3/13/2018.
 */

public class TimeOpen implements Serializable {
    int id;
    String user;
    String date;
    String time;

    public TimeOpen(int id, String user, String date, String time) {
        this.id = id;
        this.user = user;
        this.date = date;
        this.time = time;
    }

    public TimeOpen() {
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getUser() {
        return user;
    }

    public void setUser(String user) {
        this.user = user;
    }

    public String getDate() {
        return date;
    }

    public void setDate(String date) {
        this.date = date;
    }

    public String getTime() {
        return time;
    }

    public void setTime(String time) {
        this.time = time;
    }

    @Override
    public String toString() {
        return "TimeOpen{" +
                "id=" + id +
                ", user='" + user + '\'' +
                ", date='" + date + '\'' +
                ", time='" + time + '\'' +
                '}'+ "\n";
    }
}
