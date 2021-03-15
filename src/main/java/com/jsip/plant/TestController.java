package com.jsip.plant;

import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class TestController
{
    @RequestMapping("/")
    public String index() {
      return "Greetings from Spring Boot!";
    }
}
