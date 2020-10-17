(function(){var loadHandler=window['sl_{FA4BE5EF-B730-4259-89B8-FB49B5B88F6F}'];loadHandler&&loadHandler(7, '<div id="spr0_19d1a006"><div id="spr1_19d1a006" class="kern"><img id="img2_19d1a006" src="data/img2.png" width="720px" height="540px" alt="" style="left:0px;top:0px;"/><div id="spr3_19d1a006" style="left:444.625px;top:510.875px;"><div style="width:0px;"><span id="txt0_19d1a006" class="relpos" style="left:7.2px;top:4.209px;">©</span><span id="txt1_19d1a006" class="relpos" data-width="36.697266" style="left:7.195px;top:4.209px;">2012   </span><span id="txt2_19d1a006" class="relpos" data-width="108.720703" style="left:7.19px;top:4.209px;"> Dr. Feza BUZLUCA</span></div></div><div id="spr4_19d1a006" style="left:-0px;top:23.125px;"><img id="img0_19d1a006" src="data/img0.png" width="720" height="4.625" alt=""/></div><div id="spr5_19d1a006" style="top:503.25px;"><img id="img1_19d1a006" src="data/img1.png" width="720" height="5" alt=""/></div><div id="spr6_19d1a006" style="left:17px;top:505.275px;"><div style="width:0px;"><span id="txt3_19d1a006" data-width="188.753906" style="left:7.2px;top:4.209px;">http://www.faculty.itu.edu.tr/buzluca</span></div><div style="width:0px;"><span id="txt4_19d1a006" data-width="123.392578" style="left:7.2px;top:18.609px;">http://www.buzluca.info</span></div></div><div id="spr7_19d1a006"><div style="width:0px;"><span id="txt5_19d1a006" class="relpos" data-width="40.461914" style="left:7.25px;top:4.335px;">Object</span><span id="txt6_19d1a006" class="relpos" data-width="193.005859" style="left:7.245px;top:4.335px;"> Oriented Modeling and Design</span></div></div><div id="spr8_19d1a006" style="left:666.4px;top:507.835px;"><div style="width:0px;"><span id="txt7_19d1a006" style="left:7.2px;top:4.31px;">6</span></div><div style="width:0px;"><span id="txt8_19d1a006" style="left:14.95px;top:4.31px;">.</span></div><div style="width:0px;"><span id="txt9_19d1a006" style="left:18.825px;top:4.31px;">8</span></div></div></div><div id="spr2_19d1a006" class="kern"><div id="spr9_19d1a006" style="left:9px;top:31.722px;"><div style="width:0px;"><span id="txt10_19d1a006" class="relpos" data-width="78.275391" style="left:7.2px;top:0.845px;">Example:</span><span id="txt11_19d1a006" class="relpos" data-width="146.047852" style="left:7.195px;top:0.845px;"> Unit test of the </span><span id="txt12_19d1a006" class="relpos" data-width="33.064453" style="left:7.19px;top:2.673px;">Sale</span><span id="txt13_19d1a006" class="relpos" data-width="46.291992" style="left:7.185px;top:0.845px;"> class</span></div></div><div id="spr10_19d1a006" style="left:9px;top:31.722px;"><div style="width:0px;"><span id="txt14_19d1a006" class="relpos" data-width="449.595703" style="left:7.2px;top:28.445px;">Remember that we do not write all the unit tests for </span><span id="txt15_19d1a006" class="relpos" data-width="33.064453" style="left:7.195px;top:30.273px;">Sale</span><span id="txt16_19d1a006" class="relpos" data-width="193.737305" style="left:7.19px;top:28.445px;"> first; rather, we write</span></div><div style="width:0px;"><span id="txt17_19d1a006" class="relpos" data-width="447.925781" style="left:7.2px;top:50.045px;">only one test method, implement the solution in class </span><span id="txt18_19d1a006" class="relpos" data-width="33.064453" style="left:7.195px;top:51.873px;">Sale</span><span id="txt19_19d1a006" class="relpos" data-width="171.694336" style="left:7.19px;top:50.045px;"> to make it pass, and</span></div><div style="width:0px;"><span id="txt20_19d1a006" data-width="103.710938" style="left:7.2px;top:71.645px;">then repeat.</span></div></div><div id="spr11_19d1a006" style="left:9px;top:31.722px;"><div style="width:0px;"><span id="txt21_19d1a006" data-width="454.078125" style="left:7.2px;top:99.245px;">Assume that we use the unit testing framework Junit.</span></div></div><div id="spr12_19d1a006" style="left:9px;top:31.722px;"><div style="width:0px;"><span id="txt22_19d1a006" class="relpos" data-width="563.660156" style="left:7.2px;top:126.845px;">To use JUnit, you must create a test class that extends the JUnit </span><span id="txt23_19d1a006" class="relpos" data-width="71.806641" style="left:7.195px;top:128.673px;">TestCase</span></div><div style="width:0px;"><span id="txt24_19d1a006" data-width="504.799805" style="left:7.2px;top:148.445px;">class; your test class inherits various unit testing behaviors.</span></div></div><div id="spr13_19d1a006" style="left:-0px;top:210.223px;"><div style="width:0px;"><span id="txt25_19d1a006" class="relpos" data-width="156.005859" style="left:7.2px;top:0.845px;">Test code for the </span><span id="txt26_19d1a006" class="relpos" data-width="112.913086" style="left:7.195px;top:2.673px;">makeLineItem</span><span id="txt27_19d1a006" class="relpos" data-width="121.631836" style="left:7.19px;top:0.845px;"> meted of the </span><span id="txt28_19d1a006" class="relpos" data-width="33.064453" style="left:7.185px;top:2.673px;">Sale</span><span id="txt29_19d1a006" class="relpos" data-width="46.291992" style="left:7.18px;top:0.845px;"> class</span></div></div><div id="spr14_19d1a006" style="left:-0px;top:210.223px;"><div style="width:0px;"><span id="txt30_19d1a006" data-width="290.618652" style="left:7.2px;top:27.101px;">public class SaleTest extends TestCase</span></div></div><div id="spr15_19d1a006" style="left:-0px;top:210.223px;"><div style="width:0px;"><span id="txt31_19d1a006" style="left:7.2px;top:47.501px;">{</span></div></div><div id="spr16_19d1a006" style="left:-0px;top:210.223px;"><div style="width:0px;"><span id="txt32_19d1a006" data-width="240.041992" style="left:28.45px;top:67.901px;">public void testMakeLineItem(){</span></div></div><div id="spr17_19d1a006" style="left:-0px;top:210.223px;"><div style="width:0px;"><span id="txt33_19d1a006" data-width="210.034668" style="left:42.45px;top:88.301px;">Sale fixture = new Sale();   </span><span id="txt34_19d1a006" data-width="28.936523" style="left:295.2px;top:88.301px;">  // </span><span id="txt35_19d1a006" data-width="107.367950" style="left:329.994px;top:88.301px;">Tested object</span></div></div><div id="spr18_19d1a006" style="left:-0px;top:210.223px;"><div style="width:0px;"><span id="txt36_19d1a006" data-width="239.253418" style="left:42.45px;top:108.701px;">Money total = new Money(7.5);</span><span id="txt37_19d1a006" data-width="23.624023" style="left:295.2px;top:108.701px;"> // </span><span id="txt38_19d1a006" data-width="146.008087" style="left:324.619px;top:108.701px;">Supporting objects</span></div></div><div id="spr19_19d1a006" style="left:-0px;top:210.223px;"><div style="width:0px;"><span id="txt39_19d1a006" class="relpos" data-width="10.625000" style="left:7.2px;top:129.101px;">  </span><span id="txt40_19d1a006" class="relpos" style="left:17.695px;top:129.101px;"> </span><span id="txt41_19d1a006" class="relpos" data-width="242.042480" style="left:26.315px;top:129.101px;">Money price = new Money(2.5);</span></div></div><div id="spr20_19d1a006" style="left:-0px;top:210.223px;"><div style="width:0px;"><span id="txt42_19d1a006" data-width="212.500000" style="left:42.45px;top:149.501px;">ItemID id = new ItemID(1);</span></div></div><div id="spr21_19d1a006" style="top:210.223px;"><div style="width:0px;"><span id="txt43_19d1a006" data-width="575.310547" style="left:42.45px;top:169.901px;">ProductSpecification spec = new ProductSpecification(id, price, “product 1”);</span></div></div><div id="spr22_19d1a006" style="left:-0px;top:210.223px;"><div style="width:0px;"><span id="txt44_19d1a006" data-width="39.561523" style="left:42.45px;top:190.301px;">    // </span><span id="txt45_19d1a006" data-width="195.480743" style="left:87.994px;top:190.301px;">Method is being tested …</span></div></div><div id="spr23_19d1a006" style="left:-0px;top:210.223px;"><div style="width:0px;"><span id="txt46_19d1a006" class="relpos" data-width="166.248047" style="left:42.45px;top:210.701px;">fixture.makeLineItem(</span><span id="txt47_19d1a006" class="relpos" data-width="33.775879" style="left:42.445px;top:210.701px;">spec</span><span id="txt48_19d1a006" class="relpos" data-width="32.256836" style="left:42.44px;top:210.701px;">, 1);</span></div></div><div id="spr24_19d1a006" style="left:-0px;top:210.223px;"><div style="width:0px;"><span id="txt49_19d1a006" class="relpos" style="left:28.45px;top:231.101px;"> </span><span id="txt50_19d1a006" class="relpos" data-width="166.248047" style="left:37.07px;top:231.101px;">fixture.makeLineItem(</span><span id="txt51_19d1a006" class="relpos" data-width="33.775879" style="left:37.065px;top:231.101px;">spec</span><span id="txt52_19d1a006" class="relpos" data-width="32.256836" style="left:37.06px;top:231.101px;">, 2);</span></div></div><div id="spr25_19d1a006" style="top:210.223px;"><div style="width:0px;"><span id="txt53_19d1a006" data-width="365.516602" style="left:42.45px;top:251.501px;">assertTrue( fixture.getTotal().equals(total));   // </span><span id="txt54_19d1a006" style="left:410.099px;top:251.501px;">I</span><span id="txt55_19d1a006" data-width="239.051544" style="left:416.309px;top:251.501px;">s the total calculated correctly?</span></div></div><div id="spr26_19d1a006" style="left:-0px;top:210.223px;"><div style="width:0px;"><span id="txt56_19d1a006" class="relpos" style="left:7.2px;top:271.901px;"> </span><span id="txt57_19d1a006" class="relpos" data-width="18.029297" style="left:37.07px;top:271.901px;">:::</span></div></div></div></div>');})();