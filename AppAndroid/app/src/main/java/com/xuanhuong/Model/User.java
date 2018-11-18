package com.xuanhuong.Model;
import java.io.Serializable;

/**
 * Created by CR7 on 3/13/2018.
 */

public class User implements Serializable{

    private int idUser;
    private String password;
    private String username;
    private String name;
    private String idCard;

    public User() {
    }

    @Override
    public String toString() {
        return "User{" +
                "idUser=" + idUser +
                ", password='" + password + '\'' +
                ", username='" + username + '\'' +
                ", name='" + name + '\'' +
                ", idCard='" + idCard + '\'' +
                '}';
    }

    public User(int idUser, String password, String username, String name, String idCard) {
        this.idUser = idUser;
        this.password = password;
        this.username = username;
        this.name = name;
        this.idCard = idCard;
    }

    public int getIdUser() {
        return idUser;
    }

    public void setIdUser(int idUser) {
        this.idUser = idUser;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getIdCard() {
        return idCard;
    }

    public void setIdCard(String idCard) {
        this.idCard = idCard;
    }



}
