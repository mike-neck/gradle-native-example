/*
 * This Java source file was generated by the Gradle 'init' task.
 */
package com.example;

import java.util.Random;
import net.moznion.gimei.Gimei;
import net.moznion.gimei.NameUnit;
import net.moznion.gimei.name.Name;

public class App {

    native String greetingTo(String name);

    public static void main(String[] args) {
        loadLibrary();
        App app = new App();
        new Random()
                .longs(100L)
                .mapToObj(Gimei::generateName)
                .map(Name::first)
                .map(NameUnit::kanji)
                .map(app::greetingTo)
                .forEach(System.out::println);
    }

    static void loadLibrary() {
        System.loadLibrary("cpp-lib");
    }
}